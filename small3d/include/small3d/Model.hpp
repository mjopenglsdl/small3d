/*
 *  Model.hpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */
#pragma once

#include <string>
#include <vector>
#include <GL/glew.h>

namespace small3d {
  /**
   * @struct	Model
   *
   * @brief	A 3D model
   */

  struct Model {

    GLuint vaoId = 0;
    GLuint positionBufferObjectId = 0;
    GLuint indexBufferObjectId = 0;
    GLuint normalsBufferObjectId = 0;
    GLuint textureId = 0;
    GLuint uvBufferObjectId = 0;


    /**
     * @brief The vertex data. This is an array, which is to be treated as a 4 column table, holding
     * the x, y, z values in each column. The fourth column is there to assist in matrix operations.
     */

    std::vector<float> vertexData;

    /**
     * @brief Size of the vertex data, in bytes.
     */

    int vertexDataSize;

    /**
     * @brief 3 column table. Each element refers to a "row" in the vertex data table. Each "row"
     * in the index data table forms a triangle.
     *
     */

    std::vector<unsigned int> indexData;

    /**
     * @brief Size of the index data, in bytes
     */

    int indexDataSize;

    /**
     * @brief Array, to be treated as a 3 column table. Each "row" contains the x, y and z components
     * of the vector representing the normal of a vertex. The position of the "row" in the array
     * is the same as the position of the corresponding vertex "row" in the vertexData array.
     */

    std::vector<float> normalsData;

    /**
     * @brief Size of the normals data, in bytes.
     */

    int normalsDataSize;

    /**
     * @brief Array, to be treated as a 2 column table. Each "row" contains the x and y components
     * of the pixel coordinates on the model's texture image for the vertex in the corresponding
     * "row" of the vertex data "table"
     */

    std::vector<float> textureCoordsData;

    /**
     * @brief Size of the texture coordinates data, in bytes.
     */

    int textureCoordsDataSize;

    /**
     * @brief Default constructor
     */

  };
}
