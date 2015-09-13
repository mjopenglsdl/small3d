/*
 *  Model.cpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "Model.hpp"

using namespace std;

namespace small3d {

  Model::Model() {
    vertexData.clear();
    vertexDataSize = 0;
    indexData.clear();
    indexDataSize = 0;
    normalsData.clear();
    normalsDataSize = 0;
    textureCoordsData.clear();
    textureCoordsDataSize = 0;
  }

  Model::~Model(void) {

  }

}

