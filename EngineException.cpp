/*
*  EngineException.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

#include "EngineException.h"

namespace small3d {

	EngineException::EngineException() {


	}

	EngineException::EngineException(string message) {
		this->message = message;
	}

	const char* EngineException::what() const throw () {
		return message.c_str();
	}


	EngineException::~EngineException() throw() {
		// TODO Auto-generated destructor stub
	}

}

