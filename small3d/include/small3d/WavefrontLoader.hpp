/*
 *  WavefrontLoader.hpp
 *
 *  Created on: 2014/11/12
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */
#pragma once

#include "ModelLoader.hpp"
#include <vector>

namespace small3d {

  /**
   * @class	WavefrontLoader
   *
   * @brief	Class that loads a model from a wavefront .obj file, into a Model object.
   *
   */

  class WavefrontLoader : public ModelLoader {
  private:

    // Data read from .obj file
    std::vector<std::vector<float> > vertices;
    std::vector<std::vector<int> > facesVertexIndices;
    std::vector<std::vector<float> > normals;
    std::vector<std::vector<int> > facesNormalIndices;
    std::vector<std::vector<float> > textureCoords;
    std::vector<std::vector<int> > textureCoordsIndices;

    void loadVertexData(Model &model);

    void loadIndexData(Model &model);

    void loadNormalsData(Model &model);

    void loadTextureCoordsData(Model &model);

    // Make sure that no texture coordinate information is lost when the data buffers get created (vertexData,
    // indexData, normalsData and textureCoordsData) by realigning the data vectors, in order to ensure unique
    // vertex - texture coordinates pairs
    void correctDataVectors();

    void clear();

  public:

    /**
     * @brief Default constructor
     */

    WavefrontLoader();

    /**
     * @brief Destructor.
     */

    ~WavefrontLoader() = default;

    /**
     * @brief Loads a model from the given wavefront .obj file into the model object.
     *
     * @param	fileLocation	Path to the file in which the model is stored.
     * @param	model   	The model.
     */

    void load(std::string fileLocation, Model &model);

  };

}
