/*
*  EngineException.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once

#include <exception>
#include <string>

using namespace std;

namespace small3d {

	/**
	 * @class	EngineException
	 *
	 * @brief	The standard exception for small3d.
	 *
	 */

	class EngineException : public exception  {
	private:
		string message;
	public:

		/**
		 * @fn	EngineException::EngineException();
		 *
		 * @brief	Default constructor.
		 *
		 */

		EngineException();

		/**
		 * @fn	EngineException::EngineException(string message);
		 *
		 * @brief	Constructor with message.
		 *
		 * @param	message	The message.
		 */

		EngineException(string message);

		/**
		 * @fn	virtual const char* EngineException::what() const throw();
		 *
		 * @brief	Returns a null terminated character sequence that can be used to identify the exception.
		 *
		 * @return	Information about the exception.
		 */

		virtual const char* what() const throw();

		/**
		 * @fn	virtual EngineException::~EngineException() throw();
		 *
		 * @brief	Destructor.
		 *
		 */

		virtual ~EngineException() throw();
	};

} 
