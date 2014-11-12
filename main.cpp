/*
*  main.cpp
*
*  Created on: 2014/10/18
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

// Without undefining strict ANSI, compilation in MinGW fails when C++11 is enabled
#ifdef __MINGW32__
#ifdef __STRICT_ANSI__
#undef __STRICT_ANSI__
#endif
#endif

#include "google/gtest/gtest.h"
#include "Logger.h"
#include <iostream>
#include <memory>
#include <sstream>
#include "Image.h"
#include "Model.h"
#include "BoundingBoxes.h"
#include "SceneObject.h"

/* MinGW produces the following linking error, if the unit tests
 * are linked to the renderer:
 *    undefined reference to `SDL_SetMainReady'
 * This started occurring when GLEW was removed from the small3d block
 * and placed in an independent block. It probably has something to do
 * with the order in which the SDL libraries are linked (see
 * http://www.cplusplus.com/forum/beginner/110753/). It does not occur
 * in the sample game, only in these unit tests, when they are built
 * under MinGW.
 */
#ifndef __MINGW32__
#include "Renderer.h"
#endif

/* bii data directives */

// bii://dimitrikourk/small3d/resources/images/testImage.png
// bii://dimitrikourk/small3d/resources/models/Cube/CubeNoTexture.obj
// bii://dimitrikourk/small3d/resources/models/Cube/Cube.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/GoatBB/GoatBB.obj
// bii://dimitrikourk/small3d/resources/models/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.obj
// bii://dimitrikourk/small3d/resources/models/UnspecifiedAnimal/UnspecifiedAnimalWithTextureRedBlackNumbers.png

using namespace small3d;
using namespace std;

TEST(LoggerTest, LogSomething) {

	ostringstream oss;
	initLogger(oss);

	LOGINFO("It works");
	EXPECT_TRUE(oss.str().find("It works") != (string::npos));

	LOGERROR("Error test");
	EXPECT_TRUE(oss.str().find("Error test") != (string::npos));

}

TEST(ImageTest, LoadImage) {

	unique_ptr<Image> image( new Image("dimitrikourk/small3d/resources/images/testImage.png"));

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

TEST(ModelTest, LoadModel) {

	unique_ptr<Model> model(new Model());
	model->init("dimitrikourk/small3d/resources/models/Cube/Cube.obj");

	EXPECT_NE(0, model->getVertexDataComponentCount());
	EXPECT_NE(0, model->getIndexDataIndexCount());
	EXPECT_NE(0, model->getNormalsDataComponentCount());
	EXPECT_NE(0, model->getTextureCoordsDataComponentCount());

	cout << "Vertex data component count: "
		<< model->getVertexDataComponentCount() << endl << "Index count: "
		<< model->getIndexDataIndexCount() << endl
		<< "Normals data component count: "
		<< model->getNormalsDataComponentCount() << endl
		<< "Texture coordinates count: "
		<< model->getTextureCoordsDataComponentCount() << endl;

	unique_ptr<Model> modelWithNoTexture(new Model());
	modelWithNoTexture->init(
		"dimitrikourk/small3d/resources/models/Cube/CubeNoTexture.obj");

	EXPECT_NE(0, modelWithNoTexture->getVertexDataComponentCount());
	EXPECT_NE(0, modelWithNoTexture->getIndexDataIndexCount());
	EXPECT_NE(0, modelWithNoTexture->getNormalsDataComponentCount());
	EXPECT_EQ(0, modelWithNoTexture->getTextureCoordsDataComponentCount());

	cout << "Vertex data component count: "
		<< modelWithNoTexture->getVertexDataComponentCount() << endl << "Index count: "
		<< modelWithNoTexture->getIndexDataIndexCount() << endl
		<< "Normals data component count: "
		<< modelWithNoTexture->getNormalsDataComponentCount() << endl
		<< "Texture coordinates count: "
		<< modelWithNoTexture->getTextureCoordsDataComponentCount() << endl;

}

TEST(BoundingBoxesTest, LoadBoundingBoxes) {

	unique_ptr<BoundingBoxes> bboxes(new BoundingBoxes());

	bboxes->loadFromFile("dimitrikourk/small3d/samplegame/resources/models/GoatBB/GoatBB.obj");

	EXPECT_EQ(16, bboxes->vertices->size());
	EXPECT_EQ(12, bboxes->facesVertexIndexes->size());

	cout<<"Bounding boxes vertices: "<<endl;
	for (int idx = 0; idx < 16; idx++)
	{
		cout<<bboxes->vertices->at(idx)[0] << ", " <<
			bboxes->vertices->at(idx)[1] << ", " <<
			bboxes->vertices->at(idx)[2] << ", " << endl;

	}

	cout<<"Bounding boxes faces vertex indexes: "<<endl;
	for (int idx = 0; idx < 12; idx++)
	{
		cout<<bboxes->facesVertexIndexes->at(idx)[0] << ", " <<
			bboxes->facesVertexIndexes->at(idx)[1] << ", " <<
			bboxes->facesVertexIndexes->at(idx)[2] << ", " <<
			bboxes->facesVertexIndexes->at(idx)[3] << ", " << endl;

	}

	EXPECT_FALSE(bboxes->pointCollides(0.1f, 0.1f, 0.1f, 0.0f, 0.1f, 0.1f, 1.4f));

}

/*
//This cannot run on the CI environment because there is no video device available there.

// Cannot run this with MinGW (see comment above Renderer.h include directive)
#ifndef __MINGW32__
TEST(RendererTest, StartAndUse) {
	shared_ptr<Logger> log(new Logger(cout));

	shared_ptr<Configuration> cfg(new Configuration(log));

	shared_ptr<SceneObject> object(
		new SceneObject("animal",
		"dimitrikourk/small3d/resources/models/UnspecifiedAnimal/UnspecifiedAnimalWithTexture.obj",
		cfg, log, 1, "dimitrikourk/small3d/resources/models/UnspecifiedAnimal/UnspecifiedAnimalWithTextureRedBlackNumbers.png"));
	shared_ptr<vector<shared_ptr<SceneObject> > > scene(
		new vector<shared_ptr<SceneObject> >());
	scene->push_back(object);

	unique_ptr<Renderer> renderer(new Renderer(cfg, log));
	renderer->init(640, 480, false);

}
#endif
*/

int main(int argc, char **argv) {
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
