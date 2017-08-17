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
 * @brief A macro that rounds a floating point number to the second decimal digit.
 *
 * @param x The number to be rounded.
 */

#define ROUND_2_DECIMAL(x) (floorf(static_cast<float>(100 * x + 0.5)) / 100)

namespace small3d {

  /**
   * Convert an integer to a string
   * @param number The integer
   * @return The integer, converted to a string
   */
  std::string intToStr(const int number);

}
