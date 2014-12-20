/*
 *  Sound.h
 *
 *  Created on: 2014-12-14
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include "Logger.h"
#include <string>
#include <miguel/vorbis/include/vorbis/vorbisfile.h>
#include <memory>
#include <unordered_map>
#include <dimitrikourk/portaudio/include/portaudio.h>

using namespace std;

namespace small3d {

  /**
   * @class Sound
   * 
   * @brief Sound management class
   */ 

  class Sound {

  private:
    
    unordered_map<string, OggVorbis_File> *sounds;
    unordered_map<int, PaStream*> *streams;

    PaDeviceIndex defaultOutput;

  public:

    /** 
     * Constructor
     */
    Sound();
    
    /** 
     * Destructor
     */
    ~Sound();

    /**
     * Loads a sound from a file. For the moment, the file can
     * only be an .ogg file.
     *
     * @soundFilePath The path to the file, relative to the
     *                directory of execution.
     * 
     * @soundName     The name by which the loaded sound will
     *                be identified.
     */
    void load(const string &soundFilePath, const string &soundName);

    /**
     * Plays a sound.
     *
     * @soundName The name of the sound to be played.
     *
     * @repeat    Once the sound is finished playing, repeat
     *            if set to true. Otherwise, stop playing it.
     * 
     * @return    The id of the stream playing the sound
     *
     */ 
    int play(const string &soundName, const bool &repeat);

    /** 
     * Stop playing a sound.
     * 
     * @soundName The name of the sound to be stopped.
     *
     */
    void stop(const int &streamId);

    /**
     * Delete a sound from memory.
     *
     * @soundName The name of the sound to be deleted.
     *
     */
    void deleteSound(const string &soundName);

    
  };

}
