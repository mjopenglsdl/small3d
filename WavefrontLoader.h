/*
*  WavefrontLoader.h
*
*  Created on: 2014/11/12
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/
#pragma once

#include "ModelLoader.h"
#include <vector>

using namespace std;

namespace small3d {

	/**
	* @class	ModelLoader
	*
	* @brief	Class that loads a model from a wavefront .obj file, into a Model object.
	*
	*/

	class WavefrontLoader : public ModelLoader {
	private:

		// The model to which the data is loaded
		Model* model;

		// Data read from .obj file
		vector<float*> *vertices;
		vector<int*> *facesVertexIndexes;
		vector<float*> *normals;
		vector<int*> *facesNormalIndexes;
		vector<float*> *textureCoords;
		vector<int*> *textureCoordsIndexes;

		void loadVertexData();

		void loadIndexData();

		void loadNormalsData();

		void loadTextureCoordsData();

		// Make sure that no texture coordinate information is lost when the data buffers get created (vertexData,
		// indexData, normalsData and textureCoordsData) by realigning the data vectors, in order to ensure unique
		// vertex - texture coordinates pairs
		void correctDataVectors();

		void init();

		void clear();

	public:

		/**
		* @fn	WavefrontLoader::WavefrontLoader();
		*
		* @brief	Default constructor.
		*
		*/

		WavefrontLoader();

		/**
		* @fn	WavefrontLoader::~WavefrontLoader();
		*
		* @brief	Destructor.
		*
		*/

		~WavefrontLoader();

		/**
		* @fn	void WavefrontLoader::load(const string &filename, shared_ptr<Model> model);
		*
		* @brief	Loads a model from the given wavefront .obj file into the model object.
		*
		* @param	filename	Name of the file in which the model is stored.
		* @param	model   	The model.
		*/

		void load(const string &fileLocation, Model *model);

	};

}