/*
*  EngineMath.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once

#include "Matrix4x4.h"
#include <cmath>

/**
* @def	ROUND_2_DECIMAL(x) (floorf(100 * x + 0.5) / 100)
*
* @brief	A macro that rounds a floating point number to the second decimal digit.
*
* @param	x	The number to be rounded.
*/

#define ROUND_2_DECIMAL(x) (floorf(100 * x + 0.5) / 100)

namespace small3d {

	/**
	* Rotation transformation for rotating around the X axis
	* @param angle The angle to rotate by, in radians.
	* @return The X rotation matrix
	*/
	Matrix4x4 rotateX(const float &angle);

	/**
	* Rotation transformation for rotating around the Y axis
	* @param angle The angle to rotate by, in radians.
	* @return The Y rotation matrix
	*/
	Matrix4x4 rotateY(const float &angle);

	/**
	* Rotation transformation for rotating around the Z axis
	* @param angle The angle to rotate by, in radians.
	* @return The Z rotation matrix
	*/
	Matrix4x4 rotateZ(const float &angle);

	/**
	 * @fn	float dot(const Vector4 &v1, const Vector4 &v2);
	 *
	 * @brief	Dot product of two vectors
	 *
	 * @param	v1	The first Vector.
	 * @param	v2	The second Vector.
	 *
	 * @return	The dot product.
	 */

	float dot(const Vector4 &v1, const Vector4 &v2);
}
