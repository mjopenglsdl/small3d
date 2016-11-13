/*
 *  WavefrontLoader.hpp
 *
 *  Created on: 2014/11/12
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */
#pragma once

#ifndef SMALL3D_GLFW
#include <SDL.h>
#endif

#include <vector>
#include "Model.hpp"

namespace small3d {

  /**
   * @class	WavefrontLoader
   *
   * @brief	Class that loads a model from a wavefront .obj file, into a Model object.
   *
   */

  class WavefrontLoader {
  private:

    std::string basePath;

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
     *
     * @param basePath   The path under which all accessed files and directories are
     *                   to be found. If this is not set, it is assumed to be the directory
     *                   containing the application executable when using SDL, or the
     *                   directory from where the execution command is entered when 
     *                   using GLFW.
     */

    WavefrontLoader(std::string basePath = "");

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
