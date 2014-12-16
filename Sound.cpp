/*
 *  Sound.cpp
 *
 *  Created on: 2014-12-15
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "Sound.h"
#include <miguel/vorbis/include/vorbis/codec.h>
#include <dimitrikourk/portaudio/include/portaudio.h>
#include <cstdio>
#include "Exception.h"
#include <miguel/sdl2/include/SDL.h>

namespace small3d {

  Sound::Sound(){
    sounds = new unordered_map<string, OggVorbis_File>();

  }

  Sound::~Sound(){
    delete sounds;
  }

  void Sound::load(const string &soundFilePath, const string &soundName){

#if defined(_WIN32) && !defined(__MINGW32__)
    FILE *fp;
    fopen_s(&fp, (SDL_GetBasePath() + soundFilePath).c_str(), "rb");
#else
    FILE *fp = fopen((SDL_GetBasePath() + soundFilePath).c_str(), "rb");
#endif
    if (!fp)
      {
    throw Exception(
    "Could not open file " + string(SDL_GetBasePath())
      + soundFilePath);
  }
    fclose(fp);
  }
  
    void Sound::play(const string &soundName, const bool &repeat){
  }

    void Sound::stop(const string &soundName){
  }

    void Sound::deleteSound(const string &soundName){
  }
  }


