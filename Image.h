/*
*  Image.h
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
#include "Configuration.h"
#include <glenn/png/png.h>

using namespace std;

namespace small3d {


	/// Image loading class. Only handles RGB encoded data in PNG files for now.
	class Image {
	private:
		// Configuration & logging objects
		shared_ptr<Configuration> cfg;
		shared_ptr<EngineLog> log;

		int width, height;
		float* imageData;

		// Load image from a .png file
		void loadFromFile(const string &fileLocation);

	public:
		/**
		* Constructor
		* @param fileLocation Location of image file
		* @param cfg Game configuration object
		* @param log Game log
		*/
		Image(const string &fileLocation, const shared_ptr<Configuration> cfg,
			const shared_ptr<EngineLog> log);

		/**
		* Destructor
		*/
		~Image();

		/**
		* Get the image width
		* @return The image width
		*/
		int getWidth() const;

		/**
		* Get the image height
		* @return The image height
		*/
		int getHeight() const;

		/**
		* Get the image data
		* @return The image data
		*/
		float* getData() const;

	};

}
