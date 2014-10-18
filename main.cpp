#include "google/gtest/gtest.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix4x4.h"
#include "EngineLog.h"
#include "Configuration.h"
#include <iostream>
#include <memory>
#include <sstream>
#include "Image.h"

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

TEST(EngineLogTest, LogSomething) {

	ostringstream oss;

	unique_ptr<EngineLog> log(new EngineLog(oss));

	LOGINFO("It works");
	EXPECT_TRUE(oss.str().find("It works") != (string::npos));

	LOGERROR("Error test");
	EXPECT_TRUE(oss.str().find("Error test") != (string::npos));

}

TEST(EngineLogTest, VisibleOutput) {

	unique_ptr<EngineLog> log(new EngineLog(cout));

	LOGINFO("Hello");

	LOGERROR("This is an error");

}

TEST(ConfigurationTest, FindCurrentDirectory) {
	shared_ptr<EngineLog> log(new EngineLog(cout));
	unique_ptr<Configuration> conf(new Configuration(log));
}

TEST(ImageTest, LoadImage) {
	shared_ptr<EngineLog> log(new EngineLog(cout));
	shared_ptr<Configuration> conf(new Configuration(log));

	unique_ptr<Image> image( new Image("../blocks/dimitrikourk/small3d/data/testImage.png", conf, log));



	cout << "Image width " << image->getWidth() << ", height " << image->getHeight() << endl;

	float *imageData = image->getData();

	int x = 0, y = 0;

	while (y < image->getHeight()) {
		x = 0;
		while (x < image->getWidth()) {

			float *colour = &imageData[4 * y * image->getWidth() + 4 * x];

			EXPECT_GE(colour[0], 0.0f);
			EXPECT_LE(colour[0], 1.0f);
			EXPECT_GE(colour[1], 0.0f);
			EXPECT_LE(colour[1], 1.0f);
			EXPECT_GE(colour[2], 0.0f);
			EXPECT_LE(colour[2], 1.0f);
			EXPECT_EQ(1.0f, colour[3]);

			// Uncomment the following to actually see RGB values for each test image pixel
			// 			cout << "At (" << x << ", " << y << ") R: " << setprecision( 2 ) << colour[0] << endl;
			// 			cout << "At (" << x << ", " << y << ") G: " << setprecision( 2 ) << colour[1] << endl;
			// 			cout << "At (" << x << ", " << y << ") B: " << setprecision( 2 ) << colour[2] << endl;

			++x;
		}
		++y;
	}

}

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}