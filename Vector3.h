/*
*  Vector3.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once
#include <memory>

namespace small3d {

	/**
	* @struct	Vector3
	*
	* @brief	A 3 component vector.
	*
	*/

	struct Vector3 {
	public:

		/**
		 * @fn	Vector3(const float &x, const float &y, const float &z);
		 *
		 * @brief	Constructor.
		 *
		 * @param	x	The x component.
		 * @param	y	The y component.
		 * @param	z	The z component.
		 */

		Vector3(const float &x, const float &y, const float &z);

		/**
		 * @fn	~Vector3();
		 *
		 * @brief	Destructor.
		 *
		 */

		~Vector3();

		/**
		 * @fn	void getValueArray(float *valueArray);
		 *
		 * @brief	Fills a 3 element array with the x, y, and z values.
		 *
		 * @param [in,out]	valueArray	The value array.
		 */

		void getValueArray(float *valueArray);

		/**
		 * @brief	The x component.
		 */

		float x; 

		/**
		 * @brief	The y component.
		 */

		float y;

		/**
		 * @brief	The z component.
		 */

		float z;

	};

}