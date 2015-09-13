/*
 *  Model.hpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */
#pragma once

#include <string>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

using namespace std;

namespace small3d {
  /**
   * @class	Model
   *
   * @brief	A 3D model
   */

  class Model {

  public:

    /**
     * @brief	The vertex data. This is an array, which is to be treated as a 4 column table, holding
     * 			the x, y, z values in each column. The fourth column is there to assist in matrix operations.
     */

    vector<float> vertexData;

    /**
     * @brief	Size of the vertex data, in bytes.
     */

    int vertexDataSize;

    /**
     * @brief	3 column table. Each element refers to a "row" in the vertex data table. Each "row"
     * 				in the index data table forms a triangle.
     *
     */

    vector<unsigned int> indexData;

    /**
     * @brief	Size of the index data, in bytes
     */

    int indexDataSize;

    /**
     * @brief	Array, to be treated as a 3 column table. Each "row" contains the x, y and z components
     * 			of the vector representing the normal of a vertex. The position of the "row" in the array
     * 			is the same as the position of the corresponding vertex "row" in the vertexData array.
     */

    vector<float> normalsData;

    /**
     * @brief	Size of the normals data, in bytes.
     */

    int normalsDataSize;

    /**
     * @brief	Array, to be treated as a 2 column table. Each "row" contains the x and y components
     * 			of the pixel coordinates on the model's texture image for the vertex in the corresponding
     * 			"row" of the vertex data "table"
     */

    float *textureCoordsData;

    /**
     * @brief	Size of the texture coordinates data, in bytes.
     */

    int textureCoordsDataSize;

    /**
     * @brief	Number of elements in the texture coordinates array.
     */

    int textureCoordsDataComponentCount;

    /**
     * @fn	Model();
     *
     * @brief	Default constructor.
     *
     */

    Model();

    /**
     * @fn	~Model(void);
     *
     * @brief	Destructor.
     *
     */

    ~Model(void);

  };

}

