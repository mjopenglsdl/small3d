/*
 *  Sound.cpp
 *
 *  Created on: 2017-07-17
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */


#include "Sound.hpp"
#include "Logger.hpp"
#include <vector>
#include <stdexcept>
#include <cstring>
#include <vorbis/vorbisfile.h>

#define WORD_SIZE 2
#define PORTAUDIO_SAMPLE_FORMAT paInt16
#define SAMPLE_DATATYPE short

#define SOUND_ID(name, handle) name + "/" + handle

namespace small3d {

  unsigned int Sound::numInstances = 0;

  int Sound::audioCallback(const void *inputBuffer, void *outputBuffer,
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
  
  Sound::Sound(std::string soundFilePath) {
    if (numInstances == 0) {
      LOGDEBUG("No Sound instances exist. Initialising PortAudio");

      noOutputDevice = false;
    
      PaError initError = Pa_Initialize();
    
      if (initError != paNoError) {
	throw std::runtime_error("PortAudio failed to initialise: " + std::string(Pa_GetErrorText(initError)));
      }
    
      defaultOutput = Pa_GetDefaultOutputDevice();
    
      if (defaultOutput == paNoDevice) {
      
	LOGERROR("No default sound output device.");
      
	noOutputDevice = true;
      }
    }
    ++numInstances;
    this->load(soundFilePath);
  }

  Sound::~Sound() {
    --numInstances;
    if(numInstances == 0) {
      LOGDEBUG("Last Sound instance destroyed. Terminating PortAudio.");
      Pa_Terminate();
    }
  }

  void Sound::load(std::string soundFilePath) {

    if (!noOutputDevice) {
      
      OggVorbis_File vorbisFile;
      
#if defined(_WIN32) && !defined(__MINGW32__)
      FILE *fp;
      fopen_s(&fp, (soundFilePath).c_str(), "rb");
#else
      FILE *fp = fopen((soundFilePath).c_str(), "rb");
#endif
      
      if (!fp) {
        throw std::runtime_error("Could not open file " + soundFilePath);
      }
      
      if (ov_open_callbacks(fp, &vorbisFile, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
        throw std::runtime_error("Could not load sound from file " + soundFilePath);
      }
      
      vorbis_info *vi = ov_info(&vorbisFile, -1);
      
      this->soundData.channels = vi->channels;
      this->soundData.rate = (int) vi->rate;
      this->soundData.samples = static_cast<long>(ov_pcm_total(&vorbisFile, -1));
      this->soundData.size = soundData.channels * soundData.samples * WORD_SIZE;
      this->soundData.duration = static_cast<double>(soundData.samples) / static_cast<double>(soundData.rate);
      
      char pcmout[4096];
      int current_section;
      long ret = 0;
      long pos = 0;
      
      do {
        ret = ov_read(&vorbisFile, pcmout, sizeof(pcmout), 0, WORD_SIZE, 1, &current_section);
        if (ret < 0) {
          
          LOGERROR("Error in sound stream.");
          
        } else if (ret > 0) {
          
          this->soundData.data.insert(soundData.data.end(), &pcmout[0], &pcmout[ret]);
          
          pos += ret;
          
        }
      } while (ret != 0);
      
      ov_clear(&vorbisFile);
      
      fclose(fp);
      
      char soundInfo[100];
#if defined(_WIN32) && !defined(__MINGW32__)
      sprintf_s(soundInfo, "Loaded sound - channels %d - rate %d - samples %ld - size in bytes %ld",
                this->soundData.channels, this->soundData.rate, this->soundData.samples, this->soundData.size);
#else
      sprintf(soundInfo, "Loaded sound - channels %d - rate %d - samples %ld - size in bytes %ld",
              this->soundData.channels, this->soundData.rate, this->soundData.samples, this->soundData.size);
#endif
      LOGDEBUG(std::string(soundInfo));
    }
    
  }

  void Sound::play(bool repeat) {
  }

  void Sound::stop() {
  }
  
}
