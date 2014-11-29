/*
*  Exception.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: BSD 3-Clause License (see LICENSE file)
*/

#pragma once

#include <exception>
#include <string>

using namespace std;

namespace small3d {

	/**
	 * @class	Exception
	 *
	 * @brief	The standard exception for small3d.
	 *
	 */

	class Exception : public exception  {
	private:
		string message;
	public:

		/**
		 * @fn	Exception::Exception();
		 *
		 * @brief	Default constructor.
		 *
		 */

		Exception();

		/**
		 * @fn	Exception::Exception(string message);
		 *
		 * @brief	Constructor with message.
		 *
		 * @param	message	The message.
		 */

		Exception(string message);

		/**
		 * @fn	virtual const char* Exception::what() const throw();
		 *
		 * @brief	Returns a null terminated character sequence that can be used to identify the exception.
		 *
		 * @return	Information about the exception.
		 */

		virtual const char* what() const throw();

		/**
		 * @fn	virtual Exception::~Exception() throw();
		 *
		 * @brief	Destructor.
		 *
		 */

		virtual ~Exception() throw();
	};

} 
