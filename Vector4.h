/*
*  Vector4.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once

namespace small3d {

	/**
	 * @struct	Vector4
	 *
	 * @brief	A 4 component vector.
	 *
	 */

	struct Vector4 {

	public:

		/**
		 * @fn	Vector4(const float &x, const float &y, const float &z, const float &w);
		 *
		 * @brief	Full constructor.
		 *
		 * @param	x	The x component.
		 * @param	y	The y component.
		 * @param	z	The z component.
		 * @param	w	The w component.
		 */

		Vector4(const float &x, const float &y, const float &z, const float &w);

		/**
		 * @fn	~Vector4();
		 *
		 * @brief	Destructor.
		 *
		 */

		~Vector4();

		/**
		 * @fn	void getValueArray(float *valueArray);
		 *
		 * @brief	Fills a 4 element array with the x, y, z and w values.
		 *
		 * @param [in,out]	The value array.
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

		/**
		 * @brief	The w component.
		 */

		float w;
	};

}