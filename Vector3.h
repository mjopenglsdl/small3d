/*
*  Vector3.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once

namespace small3d {

	/**
	* @struct	Vector3
	*
	* @brief	A 3 component vector.
	*
	*/

	struct Vector3 {
	private:
		void sync();
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