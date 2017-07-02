/*
 *  Sound.hpp
 *
 *  Created on: 2017-07-17
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <unordered_map>
#include <portaudio.h>
#include <vector>
#include <string>

namespace small3d {

  /**
   * @class SoundData
   *
   * @brief A sound
   */
  class Sound {
  private:

    struct SoundData {
      int channels;
      int rate;
      long samples;
      long size;
      double duration;
      double startTime;
      bool repeat;
      unsigned long currentFrame;
      std::vector<char> data;
    };

    SoundData soundData;
    PaStream *stream;
    bool noOutputDevice;
    PaDeviceIndex defaultOutput;

    static unsigned int numInstances;

    static int audioCallback(const void *inputBuffer, void *outputBuffer,
			     unsigned long framesPerBuffer,
			     const PaStreamCallbackTimeInfo *timeInfo,
			     PaStreamCallbackFlags statusFlags,
			     void *userData);
    void load(std::string soundFilePath);

  public:
    Sound(std::string soundFilePath);
    ~Sound();
    void play(bool repeat = false);
    void stop();
    
  };

}
