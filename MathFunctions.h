/*
*  MathFunctions.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: BSD 3-Clause License (see LICENSE file)
*/

#pragma once

#include <dimitrikourk/glm/glm/glm.hpp>

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
	glm::mat4x4 rotateX(const float &angle);

	/**
	* Rotation transformation for rotating around the Y axis
	* @param angle The angle to rotate by, in radians.
	* @return The Y rotation matrix
	*/
	glm::mat4x4 rotateY(const float &angle);

	/**
	* Rotation transformation for rotating around the Z axis
	* @param angle The angle to rotate by, in radians.
	* @return The Z rotation matrix
	*/
	glm::mat4x4 rotateZ(const float &angle);

}
