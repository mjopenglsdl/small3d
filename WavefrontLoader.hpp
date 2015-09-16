/*
 *  WavefrontLoader.hpp
 *
 *  Created on: 2014/11/12
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */
#pragma once

#include "ModelLoader.hpp"
#include <vector>

using namespace std;

namespace small3d {

  /**
   * @class	WavefrontLoader
   *
   * @brief	Class that loads a model from a wavefront .obj file, into a Model object.
   *
   */

  class WavefrontLoader : public ModelLoader {
  private:

    // The model to which the data is loaded
    Model* model;

    // Data read from .obj file
    vector< vector<float> > vertices;
    vector<int*> *facesVertexIndexes;
    vector<vector<float> > normals;
    vector<vector<int> > facesNormalIndexes;
    vector<vector<float> > textureCoords;
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
     * @param	fileLocation	Path to the file in which the model is stored.
     * @param	model   	The model.
     */

    void load(const string &fileLocation, Model &model);

  };

}
