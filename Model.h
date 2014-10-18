/*
*  Model.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/
#pragma once

#include <string>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <vector>
#include <memory>
#include "EngineLog.h"
#include "Configuration.h"

using namespace std;

namespace small3d
{

	/// A model. It can be a simple object or a game character. It is loaded from a Wavefront .obj file.
	class Model
	{
	private:
		// Configuration & logging objects
		shared_ptr<Configuration> cfg;
		shared_ptr<EngineLog> log;

		// Basic data read from .obj file
		vector<float*> *vertices;
		vector<int*> *facesVertexIndexes;
		vector<float*> *normals;
		vector<int*> *facesNormalIndexes;
		vector<float*> *textureCoords;
		vector<int*> *textureCoordsIndexes;

		// Vertex data
		float *vertexData;
		int vertexDataSize;
		int vertexDataComponentCount;

		// Vertex index data
		unsigned int *indexData;
		int indexDataSize;
		int indexDataIndexCount;

		// Normals data
		float *normalsData;
		int normalsDataSize;
		int normalsDataComponentCount;

		// Texture coordinates data
		float *textureCoordsData;
		int textureCoordsDataSize;
		int textureCoordsDataComponentCount;

		// Load model from a Wavefront .obj file
		void loadFromFile(string fileLocation);

		// Make sure that no texture coordinate information is lost when the data buffers get created (vertexData,
		// indexData, normalsData and textureCoordsData) by realigning the data vectors, in order to ensure unique
		// vertex - texture coordinates pairs
		void correctDataVectors();

		// Delete the buffers to which the information read from the file is initially stored. To be used
		// in order to free those buffers' memory after the data that will be used by the program has been
		// generated and in the destructor, just in case.
		void deleteInitialBuffers();

	public:

		/**
		* Default constructor
		*/
		Model();

		/**
		* Initialisation of the model.
		* @param filename The model file location. This must be a Wavefront .obj file and it must have been
		* exported from Blender with the options "Triangulate faces" and "Keep Vertex Order" checked
		* @param cfg The game configuration
		* @param log The log
		*/
		void init(const string &filename,
			const shared_ptr<Configuration> cfg,
			const shared_ptr<EngineLog> log);
		~Model(void);

		/**
		* Get the vertex data, e.g. to be sent to glBindBuffer.
		* The structure of the data can be defined via the Model's state.
		* @return The vertex data
		*/
		float * getVertexData();

		/**
		* Get the size of the vertex data, in bytes.
		* @return The size of the vertex data
		*/
		int getVertexDataSize() const;

		/**
		* Get the number of components in the vertex data array
		* @return The number of vertex data components
		*/
		int getVertexDataComponentCount() const;


		/**
		* Get the index data, i.e. the indexes of each vertex to be drawn
		* when the indexed drawing flag has been set.
		* @return
		*/
		unsigned int * getIndexData();

		/**
		* Get the size of the index data
		* @return The size of the index data
		*/
		int getIndexDataSize() const;

		/**
		* Get the number of index data elements
		* @return The number of index data elements
		*/
		int getIndexDataIndexCount() const;

		/**
		* Get the normals data
		* @return The normals data
		*/
		float* getNormalsData();

		/**
		* Get the size of the normals data, in bytes
		* @return The size of the normals data, in bytes
		*/
		int getNormalsDataSize() const;

		/**
		* Get the total number of normals data components
		* @return The total number of normals data components
		*/
		int getNormalsDataComponentCount() const;

		/**
		* Get the texture coordinates data
		* @return The texture coordinates data
		*/
		float* getTextureCoordsData();

		/**
		* Get the size of the texture coordinates data, in bytes
		* @return The size of the texture coordinates data, in bytes
		*/
		int getTextureCoordsDataSize() const;

		/**
		* Get the total number of texture coordinates data components
		* @return The total number of texture coordinates data components
		*/
		int getTextureCoordsDataComponentCount() const;

	};

}

