/*
 *  Sound.hpp
 *
 *  Created on: 2014-12-14
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include "Logger.hpp"
#include <string>
#include <vorbis/vorbisfile.h>
#include <memory>
#include <unordered_map>
#include <portaudio.h>
#include "SoundData.hpp"
using namespace std;

namespace small3d {

  /**
   * @class Sound
   * @brief Sound management class
   */

  class Sound {

  private:

    unordered_map<string, SoundData*> *sounds;

    PaDeviceIndex defaultOutput;

  public:

    /**
     * @brief Constructor
     */
    Sound();

    /**
     * @brief Destructor
     */
    ~Sound();

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
     *
     */
    void play(string soundName);

    /**
     * @brief Deletes a sound from memory.
     *
     * @param soundName The name of the sound to be deleted.
     *
     */
    void deleteSound(string soundName);

  };
}
