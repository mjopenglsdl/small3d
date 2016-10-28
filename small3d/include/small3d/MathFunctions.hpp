/*
 *  MathFunctions.hpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <glm/glm.hpp>
#include <string>

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
   * @brief Rotation transformation for rotating around the X axis
   * @param angle The angle to rotate by, in radians.
   * @return The X rotation matrix
   */
  glm::mat4x4 rotateX(float angle);

  /**
   * @brief Rotation transformation for rotating around the Y axis
   * @param angle The angle to rotate by, in radians.
   * @return The Y rotation matrix
   */
  glm::mat4x4 rotateY(float angle);

  /**
   * @brief Rotation transformation for rotating around the Z axis
   * @param angle The angle to rotate by, in radians.
   * @return The Z rotation matrix
   */
  glm::mat4x4 rotateZ(float angle);

  /**
   * Convert an integer to a string
   * @param number The integer
   * @return The integer, converted to a string
   */
  std::string intToStr(int number);

}
