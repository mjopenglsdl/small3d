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
   * @class Sound
   *
   * @brief Class that loads and plays a sound from an ogg file.
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

    static bool noOutputDevice;
    static PaDeviceIndex defaultOutput;
    static unsigned int numInstances;

    static int audioCallback(const void *inputBuffer, void *outputBuffer,
			     unsigned long framesPerBuffer,
			     const PaStreamCallbackTimeInfo *timeInfo,
			     PaStreamCallbackFlags statusFlags,
			     void *userData);
    void load(std::string soundFilePath);

  public:
    /**
     * @brief Default constructor
     */
    Sound();

    /**
     * @brief Ogg file loading constructor
     * @param soundFilePath The path to the ogg file from which to load the sound.
     */
    Sound(std::string soundFilePath);

    /**
     * @brief Destructor
     */
    ~Sound();

    /**
     * @brief Play the sound.
     * @param repeat Repeat the sound after it is done playing?
     */
    void play(bool repeat = false);

    /**
     * @brief Stop playing the sound.
     */
    void stop();

    // Copy constructor
    Sound(const Sound& other);

    // Move constructor
    Sound(const Sound&& other);

    // Copy assignment
    Sound& operator=(const Sound& other);

    // Move assignment
    Sound& operator=(const Sound&& other);
    
  };

}
