/*
*  Exception.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: BSD 3-Clause License (see LICENSE file)
*/

#include "Exception.h"

namespace small3d {

	Exception::Exception() {


	}

	Exception::Exception(string message) {
		this->message = message;
	}

	const char* Exception::what() const throw () {
		return message.c_str();
	}


	Exception::~Exception() throw() {
		// TODO Auto-generated destructor stub
	}

}

