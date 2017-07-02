/*
 *  Sound.cpp
 *
 *  Created on: 2017-07-17
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "Sound.hpp"
#include <vector>

#define WORD_SIZE 2
#define PORTAUDIO_SAMPLE_FORMAT paInt16
#define SAMPLE_DATATYPE short

#define SOUND_ID(name, handle) name + "/" + handle

namespace small3d {

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
  
  Sound::Sound(std::string filename) {
  }

  void Sound::play(bool repeat) {
  }

  void Sound::stop() {
  }
  
}
