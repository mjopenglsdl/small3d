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

  int audioCallback(const void *input, void *output, 
		    unsigned long frameCount,
		    PaStreamCallbackTimeInfo *timeInfo,
		    PaStreamCallbackFlags statusFlags,
		    void *userData) {
    return paContinue;
  }

  Sound::Sound(){
    sounds = new unordered_map<string, OggVorbis_File>();
    streams = new unordered_map<int, PaStream*>();
    
    PaError error = Pa_Initialize();
    if (error != paNoError) {
      throw Exception("PortAudio failed to initialise: " + string(Pa_GetErrorText(error)));
    }
    
    defaultOutput = Pa_GetDefaultOutputDevice();
  }

  Sound::~Sound(){

    for (unordered_map<int, PaStream*>::iterator it = streams->begin(); it != streams->end(); ++it) {
      Pa_StopStream(it->second);
      Pa_CloseStream(it->second);
    }
    
    delete streams;
    
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

    char pcmout[4096];
    int current_section;
    long ret = 0;
    do{
      ret=ov_read(&vorbisFile,pcmout,sizeof(pcmout),0,2,1,&current_section);
      if (ret < 0) {
	LOGERROR("Error in sound stream.");
      } else if (ret > 0) {
	/* we don't bother dealing with sample rate changes, etc, but
	   you'll have to*/
	LOGINFO("read sound");
      }
    }
    while(ret !=0);

    
      sounds->insert(make_pair(soundName, vorbisFile));

    fclose(fp);
  }
  
  int Sound::play(const string &soundName, const bool &repeat){
    
    if (defaultOutput == paNoDevice) {
      throw Exception("No default sound output device.");
    }

    unordered_map<string, OggVorbis_File>::iterator nameSoundPair = sounds->find(soundName);

    if(nameSoundPair == sounds->end()) {
      throw Exception("Sound '" + soundName + "' has not been loaded.");
    }

    /*  vorbis_info *vi=ov_info(&nameSoundPair.second,-1);

	PaStream *stream;

	PaStreamParameters outputParams;

    

	memset(&outputParams, 0, sizeof(PaStreamParameters));
	outputParams.device = defaultOutput;
	outputParams.channelCount = vi->channels;
	outputParams.sampleFormat = paInt32;

	PaError error = Pa_OpenStream(&stream, NULL, &outputParams, vi->rate, 
	(long)ov_pcm_total(&vorbisFile,-1), paNoFlag,
	audioCallback, 
    
    */
 
  }

  void Sound::stop(const int &streamId){
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


