/*
*  Matrix4x4.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#include "Matrix4x4.h"

namespace small3d {

	Matrix4x4::Matrix4x4(const float &x1, const float &y1, const float &z1, const float &w1,
		const float &x2, const float &y2, const float &z2, const float &w2,
		const float &x3, const float &y3, const float &z3, const float &w3,
		const float &x4, const float &y4, const float &z4, const float &w4) {

			// This is basically a row major matrix, but we control the details
			// of multiplication, so it might not matter. 
			valueArray[0] = x1;
			valueArray[1] = y1; 
			valueArray[2] = z1; 
			valueArray[3] = w1;
			valueArray[4] = x2;
			valueArray[5] = y2; 
			valueArray[6] = z2; 
			valueArray[7] = w2;
			valueArray[8] = x3;
			valueArray[9] = y3; 
			valueArray[10] = z3; 
			valueArray[11] = w3;
			valueArray[12] = x4; 
			valueArray[13] = y4; 
			valueArray[14] = z4;
			valueArray[15] = w4;

	}
	
	Matrix4x4::Matrix4x4()
	{
		memset(valueArray, 0, 16*sizeof(float));
	}

	Matrix4x4::~Matrix4x4() {
		
	}

	Matrix4x4 Matrix4x4::operator*(const Matrix4x4 &m) const
	{
		Matrix4x4 result( 
			this->valueArray[0] * m.valueArray[0] + this->valueArray[1] * m.valueArray[4] + this->valueArray[2] * m.valueArray[8] + this->valueArray[3] * m.valueArray[12],
			this->valueArray[0] * m.valueArray[1] + this->valueArray[1] * m.valueArray[5] + this->valueArray[2] * m.valueArray[9] + this->valueArray[3] * m.valueArray[13],
			this->valueArray[0] * m.valueArray[2] + this->valueArray[1] * m.valueArray[6] + this->valueArray[2] * m.valueArray[10] + this->valueArray[3] * m.valueArray[14],
			this->valueArray[0] * m.valueArray[3] + this->valueArray[1] * m.valueArray[7] + this->valueArray[2] * m.valueArray[11] + this->valueArray[3] * m.valueArray[15],

			this->valueArray[4] * m.valueArray[0] + this->valueArray[5] * m.valueArray[4] + this->valueArray[6] * m.valueArray[8] + this->valueArray[7] * m.valueArray[12],
			this->valueArray[4] * m.valueArray[1] + this->valueArray[5] * m.valueArray[5] + this->valueArray[6] * m.valueArray[9] + this->valueArray[7] * m.valueArray[13],
			this->valueArray[4] * m.valueArray[2] + this->valueArray[5] * m.valueArray[6] + this->valueArray[6] * m.valueArray[10] + this->valueArray[7] * m.valueArray[14],
			this->valueArray[4] * m.valueArray[3] + this->valueArray[5] * m.valueArray[7] + this->valueArray[6] * m.valueArray[11] + this->valueArray[7] * m.valueArray[15],

			this->valueArray[8] * m.valueArray[0] + this->valueArray[9] * m.valueArray[4] + this->valueArray[10] * m.valueArray[8] + this->valueArray[11] * m.valueArray[12],
			this->valueArray[8] * m.valueArray[1] + this->valueArray[9] * m.valueArray[5] + this->valueArray[10] * m.valueArray[9] + this->valueArray[11] * m.valueArray[13],
			this->valueArray[8] * m.valueArray[2] + this->valueArray[9] * m.valueArray[6] + this->valueArray[10] * m.valueArray[10] + this->valueArray[11] * m.valueArray[14],
			this->valueArray[8] * m.valueArray[3] + this->valueArray[9] * m.valueArray[7] + this->valueArray[10] * m.valueArray[11] + this->valueArray[11] * m.valueArray[15],

			this->valueArray[12] * m.valueArray[0] + this->valueArray[13] * m.valueArray[4] + this->valueArray[14] * m.valueArray[8] + this->valueArray[15] * m.valueArray[12],
			this->valueArray[12] * m.valueArray[1] + this->valueArray[13] * m.valueArray[5] + this->valueArray[14] * m.valueArray[9] + this->valueArray[15] * m.valueArray[13],
			this->valueArray[12] * m.valueArray[2] + this->valueArray[13] * m.valueArray[6] + this->valueArray[14] * m.valueArray[10] + this->valueArray[15] * m.valueArray[14],
			this->valueArray[12] * m.valueArray[3] + this->valueArray[13] * m.valueArray[7] + this->valueArray[14] * m.valueArray[11] + this->valueArray[15] * m.valueArray[15]

			);
		return result;
	}

	Vector4 Matrix4x4::operator*( const Vector4 &v ) const
	{
		// In effect, these are not really matrices and vectors, but arrays and variables and post-multiplying with 
		// column major matrices produces the same result as pre-multiplying with row-major matrices so 
		// this will work due to lucky programming whateverness...

		return (v) * (*this);
	}

	Vector4 operator*(const Vector4 &v, const Matrix4x4 &m )
	{
		Vector4 result( v.x * m.valueArray[0] + v.y * m.valueArray[4] + v.z * m.valueArray[8] + v.w * m.valueArray[12],
			v.x * m.valueArray[1] + v.y * m.valueArray[5] + v.z * m.valueArray[9] + v.w * m.valueArray[13],
			v.x * m.valueArray[2] + v.y * m.valueArray[6] + v.z * m.valueArray[10] + v.w * m.valueArray[14],
			v.x * m.valueArray[3] + v.y * m.valueArray[7] + v.z * m.valueArray[11] + v.w * m.valueArray[15]);
		return result;
	}

}