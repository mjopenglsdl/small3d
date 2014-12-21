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
#include <cstring>
#include "Exception.h"
#include <miguel/sdl2/include/SDL.h>
#include <iostream>

using namespace std;

namespace small3d {

  static int audioCallback( const void *inputBuffer, void *outputBuffer,
                            unsigned long framesPerBuffer,
                            const PaStreamCallbackTimeInfo* timeInfo,
                            PaStreamCallbackFlags statusFlags,
                            void *userData )
  {

    int result = paContinue;
   
    SoundData *soundData = (SoundData*)userData;
    short *out = (short*)outputBuffer;
    unsigned long startPos = soundData -> currentFrame * soundData-> channels;
    unsigned long endPos = startPos + framesPerBuffer * soundData-> channels;

    if (endPos > (unsigned long) soundData->samples * 2 * soundData->channels) {
      endPos = (unsigned long) soundData->samples * 2 * soundData->channels;
      result = paAbort;
      memset(out, 0, endPos - startPos);
      cout<<"COMPLETE"<<endl;
    }

    for( unsigned long i= startPos; i< endPos; i += soundData->channels )
      {
	for(int c = 0; c < soundData->channels; ++c)
	  {
	    *out++ = ((short*)soundData->data)[i + c];
	  }
      }
    soundData->currentFrame += framesPerBuffer;
    return result;
  }

  Sound::Sound(){
    sounds = new unordered_map<string, SoundData*>();
    
    PaError error = Pa_Initialize();

    if (error != paNoError) {
      throw Exception("PortAudio failed to initialise: " + string(Pa_GetErrorText(error)));
    }
    
    defaultOutput = Pa_GetDefaultOutputDevice();
  }

  Sound::~Sound(){
    
    for (unordered_map<string, SoundData*>::iterator it = sounds->begin();
	 it != sounds->end(); ++it)
      {
	LOGINFO("Deleting sound '" + it->first +"'.");
	delete it->second;
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

    SoundData *soundData = new SoundData();
    
    soundData->channels = vi->channels;
    soundData->rate = vi->rate;
    soundData->samples = (long)ov_pcm_total(&vorbisFile,-1);

    /*
      I have made some assumptions here that seem to work for the
      time being. I multiply the samples by the number of channels
      because, if I have understood correctly, vorbis will interleave
      the samples if there are more than 1 channels. And then I
      multiply by 2 because vorbis assumes a 16-bit buffer
      destination. (http://www.nothings.org/stb_vorbis/)
    */
    soundData->size = soundData->channels * soundData->samples * 2;

    char pcmout[4096];
    soundData->data = new char[soundData->size];

    int current_section;
    long ret = 0;
    long pos = 0;

    do{
      ret=ov_read(&vorbisFile,pcmout,sizeof(pcmout),0,2,1,&current_section);

      if (ret < 0) {

	LOGERROR("Error in sound stream.");

      } else if (ret > 0) {
	
	memcpy(&soundData->data[pos], pcmout, ret);
	pos += ret;

	/*
	  char readResult[100];
	  sprintf(readResult, "Read %d bytes and copied them up to position %d", ret, pos);
	  LOGINFO(string(readResult));
	*/
      }
    }
    while(ret !=0);

    sounds->insert(make_pair(soundName, soundData));

    ov_clear(&vorbisFile);
    fclose(fp);
    char soundInfo[100];
    sprintf(soundInfo, "Loaded sound %s - channels %d - rate %d - samples %d - size in bytes %d", soundName.c_str(), 
	    soundData->channels, soundData->rate, soundData->samples, soundData->
	    size);    
    LOGINFO(string(soundInfo));
  }
  
  int Sound::play(const string &soundName, const bool &repeat){
    
    if (defaultOutput == paNoDevice) {
      throw Exception("No default sound output device.");
    }

    unordered_map<string, SoundData*>::iterator nameSoundPair = sounds->find(soundName);

    if(nameSoundPair == sounds->end()) {
      throw Exception("Sound '" + soundName + "' has not been loaded.");
    }

    SoundData *soundData = nameSoundPair->second;
      
    PaStreamParameters outputParams;

    memset(&outputParams, 0, sizeof(PaStreamParameters));
    outputParams.device = defaultOutput;
    outputParams.channelCount = soundData->channels;
    outputParams.suggestedLatency = Pa_GetDeviceInfo( outputParams.device )->defaultLowOutputLatency;
    outputParams.hostApiSpecificStreamInfo = NULL;

    // Vorbis has produced 16-bit integers I guess...
    // (http://www.nothings.org/stb_vorbis/)
    outputParams.sampleFormat = paInt16;

    PaStream *stream;
    
    soundData->currentFrame = 0;

    PaError error = Pa_OpenStream(&stream, NULL, &outputParams, soundData->rate,
				  32, paNoFlag,
				  audioCallback, soundData);
    if (error != paNoError){
      throw Exception("Failed to open PortAudio stream: " + string(Pa_GetErrorText(error)));
    }
    LOGINFO("Playing..");
    error = Pa_StartStream(stream);
    if (error != paNoError){
      throw Exception("Failed to start stream: " + string(Pa_GetErrorText(error)));
    }
    Pa_Sleep(2*1000);
    LOGINFO("Done");
    Pa_CloseStream(stream);
    
  }

  void Sound::stop(const int &streamId){
    throw Exception("Stopping sounds has not been implemented yet.");
  }

  void Sound::deleteSound(const string &soundName){

    unordered_map<string, SoundData*>::iterator nameSoundPair = sounds->find(soundName);

    if(nameSoundPair != sounds->end())
      {
	delete nameSoundPair->second;
	sounds->erase(soundName);
      }
  }
}


