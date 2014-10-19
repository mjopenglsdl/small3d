/*
*  EngineMath.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#include "EngineMath.h"
#include <cmath>

namespace small3d {

	Matrix4x4 rotateX(const float &angle)
	{
		return Matrix4x4(1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, std::cos(angle), -std::sin(angle), 0.0f,
			0.0f, std::sin(angle), std::cos(angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	}

	Matrix4x4 rotateY(const float &angle)
	{
		return Matrix4x4(std::cos(angle), 0.0f, std::sin(angle), 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			-std::sin(angle), 0.0f, std::cos(angle), 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);

	}

	Matrix4x4 rotateZ(const float &angle)
	{
		return Matrix4x4(std::cos(angle), -std::sin(angle), 0.0f,  0.0f,
			std::sin(angle), std::cos(angle), 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
	}

	float dot( const Vector4 &v1, const Vector4 &v2 )
	{
		return v1.x*v2.x + v1.y * v2.y + v1.z * v1.z + v1.w * v1.w;
	}

}