/*
 *  SoundPlayer.cpp
 *
 *  Created on: 2014-12-15
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "SoundPlayer.hpp"
#include "Exception.hpp"
#include <cstring>

#define WORD_SIZE 2
#define PORTAUDIO_SAMPLE_FORMAT paInt16
#define SAMPLE_DATATYPE short

#define SOUND_ID(name, handle) name + "/" + handle

using namespace std;

namespace small3d {

  static int audioCallback(const void *inputBuffer, void *outputBuffer,
                           unsigned long framesPerBuffer,
                           const PaStreamCallbackTimeInfo *timeInfo,
                           PaStreamCallbackFlags statusFlags,
                           void *userData) {

    int result = paContinue;
    SoundData *soundData = static_cast<SoundData *>(userData);

    if (soundData->startTime == 0) {
      soundData->startTime = timeInfo->currentTime - 0.1;
    } else if (timeInfo->currentTime - soundData->startTime > soundData->duration) {
      if (soundData->repeat) {
        soundData->startTime = timeInfo->currentTime - 0.1;
        soundData->currentFrame = 0;
      }
      else
      {
        return paAbort;
      }
    }

    SAMPLE_DATATYPE *out = static_cast<SAMPLE_DATATYPE *>(outputBuffer);
    unsigned long startPos = soundData->currentFrame * static_cast<unsigned long>(soundData->channels);
    unsigned long endPos = startPos + framesPerBuffer * static_cast<unsigned long>(soundData->channels);

    if (endPos > static_cast<unsigned long>(soundData->samples) * WORD_SIZE * soundData->channels) {
      endPos = static_cast<unsigned long>(soundData->samples) * WORD_SIZE * soundData->channels;
      result = paAbort;
    }

    for (unsigned long i = startPos; i < endPos; i += static_cast<unsigned long>(soundData->channels)) {
      for (int c = 0; c < soundData->channels; ++c) {
        *out++ = (reinterpret_cast<short *>(soundData->data.data()))[i + c];
      }
    }

    soundData->currentFrame += framesPerBuffer;

    return result;
  }

  SoundPlayer::SoundPlayer(string basePath) {

    noOutputDevice = false;

    this->basePath = basePath;
    
    PaError initError = Pa_Initialize();

    if (initError != paNoError) {
      throw Exception("PortAudio failed to initialise: " + string(Pa_GetErrorText(initError)));
    }

    defaultOutput = Pa_GetDefaultOutputDevice();

    if (defaultOutput == paNoDevice) {

      LOGERROR("No default sound output device.");

      noOutputDevice = true;
    }
  }

  SoundPlayer::~SoundPlayer() {

    for (auto it = streams.begin(); it != streams.end(); ++it) {
      Pa_AbortStream(it->second);
      Pa_CloseStream(it->second);
    }

    Pa_Terminate();
  }

  void SoundPlayer::load(string soundFilePath, string soundName) {

    if (!noOutputDevice) {

    OggVorbis_File vorbisFile;

#if defined(_WIN32) && !defined(__MINGW32__)
    FILE *fp;
    fopen_s(&fp, (basePath + soundFilePath).c_str(), "rb");
#else
    FILE *fp = fopen((basePath + soundFilePath).c_str(), "rb");
#endif

    if (!fp) {
      throw Exception(
          "Could not open file " + basePath + soundFilePath);
    }

    if (ov_open_callbacks(fp, &vorbisFile, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
      throw Exception(
          "Could not load sound from file " + basePath + soundFilePath);
    }

    vorbis_info *vi = ov_info(&vorbisFile, -1);

    SoundData soundData;

    soundData.channels = vi->channels;
    soundData.rate = (int) vi->rate;
    soundData.samples = static_cast<long>(ov_pcm_total(&vorbisFile, -1));
    soundData.size = soundData.channels * soundData.samples * WORD_SIZE;
    soundData.duration = static_cast<double>(soundData.samples) / static_cast<double>(soundData.rate);

    char pcmout[4096];
    int current_section;
    long ret = 0;
    long pos = 0;

    do {
      ret = ov_read(&vorbisFile, pcmout, sizeof(pcmout), 0, WORD_SIZE, 1, &current_section);
      if (ret < 0) {

        LOGERROR("Error in sound stream.");

      } else if (ret > 0) {

        soundData.data.insert(soundData.data.end(), &pcmout[0], &pcmout[ret]);

        pos += ret;

      }
    } while (ret != 0);

    sounds.insert(make_pair(soundName, soundData));

    ov_clear(&vorbisFile);

    fclose(fp);

    char soundInfo[100];
#if defined(_WIN32) && !defined(__MINGW32__)
    sprintf_s(soundInfo, "Loaded sound %s - channels %d - rate %d - samples %ld - size in bytes %ld", soundName.c_str(),
            soundData.channels, soundData.rate, soundData.samples, soundData.size);
#else
    sprintf(soundInfo, "Loaded sound %s - channels %d - rate %d - samples %ld - size in bytes %ld", soundName.c_str(),
            soundData.channels, soundData.rate, soundData.samples, soundData.size);
#endif
    LOGINFO(string(soundInfo));
    }

  }

  void SoundPlayer::play(string soundName, string handle, bool repeat) {

    if (!noOutputDevice) {

      auto nameSoundPair = sounds.find(soundName);

      if (nameSoundPair == sounds.end()) {
        throw Exception("Sound '" + soundName + "' has not been loaded.");
      }

      SoundData *soundData = &nameSoundPair->second;

      PaStreamParameters outputParams;

      memset(&outputParams, 0, sizeof(PaStreamParameters));
      outputParams.device = defaultOutput;
      outputParams.channelCount = soundData->channels;
      outputParams.hostApiSpecificStreamInfo = NULL;

      outputParams.sampleFormat = PORTAUDIO_SAMPLE_FORMAT;

      auto idStreamDataPair = streamData.find(SOUND_ID(soundName, handle));

      if (idStreamDataPair == streamData.end()) {
        streamData.insert(make_pair(SOUND_ID(soundName, handle), nameSoundPair->second));
        idStreamDataPair = streamData.find(SOUND_ID(soundName , handle));
      }

      idStreamDataPair->second.currentFrame = 0;
      idStreamDataPair->second.startTime = 0;

      idStreamDataPair->second.repeat = repeat;

      PaError error;

      auto handleStreamPair = streams.find(SOUND_ID(soundName, handle));
      if (handleStreamPair != streams.end()) {

        Pa_AbortStream(handleStreamPair->second);

        error = Pa_StartStream(handleStreamPair->second);
        if (error != paNoError) {
          throw Exception("Failed to start stream: " + string(Pa_GetErrorText(error)));
        }

      } else {

        PaStream *stream = nullptr;

        error = Pa_OpenStream(&stream, NULL, &outputParams, soundData->rate,
                              1024, paNoFlag,
                              audioCallback, &idStreamDataPair->second);
        if (error != paNoError) {
          throw Exception("Failed to open PortAudio stream: " + string(Pa_GetErrorText(error)));
        }

        error = Pa_StartStream(stream);
        if (error != paNoError) {
          throw Exception("Failed to start stream: " + string(Pa_GetErrorText(error)));
        }

        streams.insert(make_pair(SOUND_ID(soundName, handle), stream));
      }

    }
  }

  void SoundPlayer::stop(string soundName, string handle) {
    if (!noOutputDevice) {

      auto nameSoundPair = sounds.find(soundName);

      if (nameSoundPair == sounds.end()) {
        throw Exception("Sound '" + soundName + "' has not been loaded.");
      }

      auto soundData = nameSoundPair->second;

      auto handleStreamPair = streams.find(SOUND_ID(soundName, handle));
      if (handleStreamPair == streams.end()) {
        throw Exception("Sound handle '" + handle + "' does not exist.");
      }

      auto stream = handleStreamPair->second;

      Pa_AbortStream(stream);

    }

  }

  void SoundPlayer::clear(string soundName) {

    vector<string> removals;

    for (auto handleStreamPair = streams.begin(); handleStreamPair != streams.end(); ++handleStreamPair) {
      if (handleStreamPair->first.compare(0, soundName.length(), soundName) == 0) {
        Pa_AbortStream(handleStreamPair->second);
        Pa_CloseStream(handleStreamPair->second);
        removals.push_back(handleStreamPair->first);
      }
    }

    for (auto removal = removals.begin(); removal != removals.end(); ++removal) {
      streams.erase(removal->data());
    }

    removals.clear();

    for (auto handleStreamDataPair = streamData.begin(); handleStreamDataPair != streamData.end();
         ++handleStreamDataPair ) {
      if (handleStreamDataPair->first.compare(0, soundName.length(), soundName) == 0) {
        removals.push_back(handleStreamDataPair->first);
      }
    }

    for (auto removal = removals.begin(); removal != removals.end(); ++removal) {
      streamData.erase(removal->data());
    }


    auto nameSoundPair = sounds.find(soundName);

    if (nameSoundPair == sounds.end()) {
      throw Exception("Sound '" + soundName + "' has not been loaded or has already been deleted.");
    }

    sounds.erase(soundName);
  }
}
