/*
 *  MathFunctions.cpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "MathFunctions.hpp"

namespace small3d {

  std::string intToStr(const int number)
  {
    char buffer[100];
#if defined(_WIN32) && !defined(__MINGW32__)
    sprintf_s(buffer,"%d",number);
#else
    sprintf(buffer,"%d",number);
#endif
    return std::string(buffer);
  }
}
