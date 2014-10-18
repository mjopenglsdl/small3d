#include "google/gtest/gtest.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include <iostream>

int sum(int a, int b) {return a+b;}

using namespace small3d;
using namespace std;

TEST(MatrixTest, Multiply) {
	
	Matrix4x4 mat(2.0f, 3.0f, 4.0f, 5.0f,
		2.0f, 3.0f, 4.0f, 5.0f,
		2.0f, 3.0f, 4.0f, 5.0f,
		2.0f, 3.0f, 4.0f, 5.0f);

	Matrix4x4 mat2 = mat * mat;

	EXPECT_EQ(28.0f, mat2.valueArray[0]);
}

TEST(VectorMatrixTest, Multiply) {

	Matrix4x4 mat(2.0f, 3.0f, 4.0f, 5.0f,
		2.0f, 3.0f, 4.0f, 5.0f,
		2.0f, 3.0f, 4.0f, 5.0f,
		2.0f, 3.0f, 4.0f, 5.0f);

	Vector4 vec(2.0f, 2.0f, 2.0f, 2.0f);

	Vector4 result = vec * mat;

	EXPECT_EQ(16.0f, result.x);

	Vector4 result2 = mat * vec;

	EXPECT_EQ(result.x, result2.x);
	EXPECT_EQ(result.y, result2.y);
	EXPECT_EQ(result.z, result2.z);
	EXPECT_EQ(result.w, result2.w);
}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}