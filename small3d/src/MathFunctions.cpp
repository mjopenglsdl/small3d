/*
 *  MathFunctions.cpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "MathFunctions.hpp"

namespace small3d {

  glm::mat4x4 rotateX(float angle)
  {
    return glm::mat4x4(1.0f, 0.0f, 0.0f, 0.0f,
		       0.0f, std::cos(angle), -std::sin(angle), 0.0f,
		       0.0f, std::sin(angle), std::cos(angle), 0.0f,
		       0.0f, 0.0f, 0.0f, 1.0f
		       );
  }

  glm::mat4x4 rotateY(float angle)
  {
    return glm::mat4x4(std::cos(angle), 0.0f, std::sin(angle), 0.0f,
		       0.0f, 1.0f, 0.0f, 0.0f,
		       -std::sin(angle), 0.0f, std::cos(angle), 0.0f,
		       0.0f, 0.0f, 0.0f, 1.0f
		       );

  }

  glm::mat4x4 rotateZ(float angle)
  {
    return glm::mat4x4(std::cos(angle), -std::sin(angle), 0.0f,  0.0f,
		       std::sin(angle), std::cos(angle), 0.0f, 0.0f,
		       0.0f, 0.0f, 1.0f, 0.0f,
		       0.0f, 0.0f, 0.0f, 1.0f
		       );
  }

}
