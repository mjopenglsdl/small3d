/*
*  Model.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

#include "Model.h"

using namespace std;

namespace small3d
{

	Model::Model() {
		vertexData = NULL;
		vertexDataSize = 0;
		vertexDataComponentCount = 0;
		indexData = NULL;
		indexDataSize = 0;
		indexDataIndexCount = 0;
		normalsData = NULL;
		normalsDataSize = 0;
		normalsDataComponentCount = 0;
		textureCoordsData = NULL;
		textureCoordsDataSize = 0;
		textureCoordsDataComponentCount = 0;
	}

	Model::~Model(void)
	{
		if (vertexData != NULL)
		{
			delete[] vertexData;
		}

		if (indexData != NULL)
		{
			delete[] indexData;
		}

		if (normalsData != NULL)
		{
			delete[] normalsData;
		}

		if (textureCoordsData != NULL)
		{
			delete[] textureCoordsData;
		}
	}

}

