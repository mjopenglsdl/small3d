/*
*  Configuration.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#include "Configuration.h"

#include "miguel/sdl2/include/SDL.h"
#include "EngineException.h"

using namespace std;

namespace small3d {

	Configuration::Configuration(shared_ptr<EngineLog> log) {
		this->log = log;
		LOGINFO("Configuration object initialised");
		this->findHomeDirectory();
	}

	Configuration::~Configuration() {
		LOGINFO("Configuration object being destroyed");
	}

	string Configuration::getHomeDirectory() {
		return homeDirectory;
	}

	void Configuration::findHomeDirectory() {
		this->homeDirectory = string(SDL_GetBasePath());
		LOGINFO("Configuration: found home directory: " + homeDirectory);

	}

} 

