/*
*  Vector3.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#include "Vector3.h"

namespace small3d {

	Vector3::Vector3(const float &x, const float &y, const float &z) {

		this->x = x;
		this->y = y;
		this->z = z;
		
	}

	Vector3::~Vector3() {
		if (valueArray != NULL) {
			delete[] valueArray;
		}
	}

	float* Vector3::getValueArray()
	{
		if (valueArray != NULL) {
			delete[] valueArray;
		}

		valueArray = new float[3];
		
		valueArray[0] = x;
		valueArray[1] = y;
		valueArray[2] = z;

		return valueArray;
	}

}