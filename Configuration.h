/*
*  Configuration.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once

#include <string>
#include <memory>
#include "EngineLog.h"

using namespace std;

namespace small3d {

	/**
	* @class	Configuration
	*
	* @brief	Configuration utility for small3d. For the moment, it can just
	* 			figure out the current path from which the application is running.
	*
	*/

	class Configuration {
	private:
		shared_ptr<EngineLog> log;
		string homeDirectory;
		void findHomeDirectory();
	public:
		/**
		* Constructor
		*/
		Configuration(shared_ptr<EngineLog> log);

		/**
		* Destructor
		*/
		~Configuration();

		/**
		* Get the home directory of the application
		* @return The home directory
		*/
		string getHomeDirectory();
	};

} 
