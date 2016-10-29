/*
*  Exception.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*     License: BSD 3-Clause License (see LICENSE file)
*/

#include "Exception.hpp"

namespace small3d {

  Exception::Exception() {

  }

  Exception::Exception(std::string message) : message(message) {

  }

  const char *Exception::what() const noexcept {
    return message.c_str();
  }


}
