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
#include <cstdio>
#include "Exception.h"
#include <miguel/sdl2/include/SDL.h>

namespace small3d {

  Sound::Sound(){
    sounds = new unordered_map<string, OggVorbis_File>();
    
    PaError error = Pa_Initialize();
    if (error != paNoError) {
      throw Exception("PortAudio failed to initialise: " + string(Pa_GetErrorText(error)));
    }
    
    defaultOutput = Pa_GetDefaultOutputDevice();
  }

  Sound::~Sound(){
    
    for (unordered_map<string, OggVorbis_File>::iterator it = sounds->begin();
	 it != sounds->end(); ++it)
      {
	LOGINFO("Deleting sound " + it->first);
	ov_clear(&it->second);
      }

    delete sounds;
    Pa_Terminate();
  }

  void Sound::load(const string &soundFilePath, const string &soundName){
    OggVorbis_File vorbisFile;
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
    if(ov_open_callbacks(fp, &vorbisFile, NULL, 0, OV_CALLBACKS_NOCLOSE) < 0) {
      throw Exception(
		      "Could not load sound from file " + string(SDL_GetBasePath())
		      + soundFilePath);
    }

    vorbis_info *vi=ov_info(&vorbisFile,-1);

    char soundInfo[100];

    sprintf(soundInfo, "Loaded sound %s - channels %d - rate %d - samples %d", soundName.c_str(), 
	    vi->channels, vi->rate, (long)ov_pcm_total(&vorbisFile,-1));
    
    LOGINFO(string(soundInfo));
    
    sounds->insert(make_pair(soundName, vorbisFile));

    fclose(fp);
  }
  
  void Sound::play(const string &soundName, const bool &repeat){
    if (defaultOutput == paNoDevice) {
      throw Exception("No default sound output device.");
    }

    unordered_map<string, OggVorbis_File>::iterator nameSoundPair = sounds->find(soundName);

    if(nameSoundPair == sounds->end()) {
      throw Exception("Sound '" + soundName + "' has not been loaded.");
    }
    

  }

  void Sound::stop(const string &soundName){
    throw Exception("Stopping sounds has not been implemented yet.");
  }

  void Sound::deleteSound(const string &soundName){

    unordered_map<string, OggVorbis_File>::iterator nameSoundPair = sounds->find(soundName);

    if(nameSoundPair != sounds->end())
      {
	ov_clear(&nameSoundPair->second);
	sounds->erase(soundName);
      }
  }
}


