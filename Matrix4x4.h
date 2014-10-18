/*
*  Matrix4x4.h
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#pragma once

#include <memory>
#include "Vector4.h"

using namespace std;

/**
* @namespace	small3d
*
* @brief	The namespace of the small3d engine.
*/

namespace small3d {

	/**
	* @struct	Matrix4x4
	*
	* @brief	A 4x4 matrix
	*
	*/

	struct Matrix4x4 {

	public:

		/**
		* @fn	Matrix4x4();
		*
		* @brief	Default constructor.
		*
		*/
		Matrix4x4();

		/**
		 * @fn	Matrix4x4(const float &x1, const float &y1, const float &z1, const float &w1,
		 * 		const float &x2, const float &y2, const float &z2, const float &w2, const float &x3,
		 * 		const float &y3, const float &z3, const float &w3, const float &x4, const float &y4,
		 * 		const float &z4, const float &w4);
		 *
		 * @brief	Full constructor.
		 *
		 * @param	x1	The first x value.
		 * @param	y1	The first y value.
		 * @param	z1	The first z value.
		 * @param	w1	The first w value.
		 * @param	x2	The second x value.
		 * @param	y2	The second y value.
		 * @param	z2	The second z value.
		 * @param	w2	The second w value.
		 * @param	x3	The third x value.
		 * @param	y3	The third y value.
		 * @param	z3	The third z value.
		 * @param	w3	The third w value.
		 * @param	x4	The fourth x value.
		 * @param	y4	The fourth y value.
		 * @param	z4	The fourth z value.
		 * @param	w4	The fourth w value.
		 */

		Matrix4x4(const float &x1, const float &y1, const float &z1, const float &w1,
			const float &x2, const float &y2, const float &z2, const float &w2,
			const float &x3, const float &y3, const float &z3, const float &w3,
			const float &x4, const float &y4, const float &z4, const float &w4);
		~Matrix4x4();

		float valueArray[16];

		/**
		 * @fn	Matrix4x4 Matrix4x4::operator*(Matrix4x4 m) const;
		 *
		 * @brief	Multiplication operator for other matrices.
		 *
		 * @param	m	The Matrix4x4 to process.
		 *
		 * @return	The resulting vector of the operation.
		 */

		Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &m) const;

		/**
		 * @fn	Vector4 operator*( const Vector4 &v ) const;
		 *
		 * @brief	Multiplication operator for matrix * vector.
		 *
		 * @param	v	The vector.
		 *
		 * @return	The result of the operation.
		 */

		Vector4 operator*( const Vector4 &v ) const;

	};

	/**
	 * @fn	Vector4 operator*(const Vector4 v, const Matrix4x4 m );
	 *
	 * @brief	Multiplication operator for vector * matrix.
	 *
	 * @param	v	The vector.
	 * @param	m	The matrix.
	 *
	 * @return	The resulting vector of the operation.
	 */

	Vector4 operator*(const Vector4 &v, const Matrix4x4 &m );

}