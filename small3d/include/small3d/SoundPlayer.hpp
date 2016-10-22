/*
 *  SoundPlayer.hpp
 *
 *  Created on: 2014-12-14
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include "Logger.hpp"
#include <string>
#include <vorbis/vorbisfile.h>
#include "SoundData.hpp"

using namespace std;

namespace small3d {

  /**
   * @class SoundPlayer
   * @brief Sound management class
   */

  class SoundPlayer {

  private:

    unordered_map<string, SoundData> sounds;

    unordered_map<string, PaStream* > streams;

    unordered_map<string, SoundData> streamData;


    bool noOutputDevice;

    PaDeviceIndex defaultOutput;

  public:

    /**
     * @brief Constructor
     */
    SoundPlayer();

    /**
     * @brief Destructor
     */
    ~SoundPlayer();

    /**
     * @brief Loads a sound from a file. For the moment, the file can
     * only be an .ogg file.
     *
     * @param soundFilePath The path to the file, relative to the
     *                      directory of execution.
     *
     * @param soundName     The name by which the loaded sound will
     *                      be identified.
     */
    void load(string soundFilePath, string soundName);

    /**
     * @brief Plays a sound.
     *
     * @param soundName The name of the sound to be played.
     * @param handle The handle of the specific sound instance. You set it here. Then, to stop playing the
     *               sound, you can call the stop function with the same handle. To repeat playing it
     *               once it is finished, you call play with it again. To create a new sound instance
     *               (in order to play the same sound more than once concurrently), you call play again
     *               with the same soundName and a new handle.
     * @param repeat Automatically repeat the sound from the beginning, once it has finished playing.
     *
     */
    void play(string soundName, string handle, bool repeat = false);

    /**
     * @brief Stop playing a sound.
     * @param soundName The name of the sound.
     * @param handle The handle of the specific instance of the sound to be stopped.
     */
    void stop(string soundName, string handle);

    /**
     * @brief Deletes a sound from memory.
     *
     * @param soundName The name of the sound to be deleted.
     *
     */
    void clear(string soundName);

  };
}
