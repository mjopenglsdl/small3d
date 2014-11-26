/*
* SceneObject.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#include "SceneObject.h"
#include <sstream>
#include <iomanip>
#include "Exception.h"
#include "ModelLoader.h"
#include "WavefrontLoader.h"
#include <memory>

using namespace std;

namespace small3d {

	void SceneObject::initPropVectors() {
		this->colour = shared_ptr<glm::vec4>(new glm::vec4(0, 0 ,0, 0));
		this->offset = shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
		this->rotation = shared_ptr<glm::vec3>(new glm::vec3(0, 0 ,0));
	}

	SceneObject::SceneObject(const string &name, const string &modelPath,
		const int &numFrames, const string &texturePath, 
		const string &boundingBoxesPath) {
			initLogger();
			this->name = name;
			animating = false;
			framesWaited = 0;
			frameDelay = 1;
			currentFrame = 0;
			this->numFrames = numFrames;

			model = new Model[numFrames];
			unique_ptr<ModelLoader> loader(new WavefrontLoader());

			if (numFrames > 1) {
				LOGINFO("Loading " + name + " animated model (this may take a while):");
				for (int idx = 0; idx < numFrames; ++idx) {
					stringstream lss;
					lss << "Frame " << idx + 1 << " of " << numFrames << "...";
					LOGINFO(lss.str());
					stringstream ss;
					ss << setfill('0') << setw(6) << idx + 1;
					string frameNum = ss.str();
					loader->load(modelPath + "_" + frameNum + ".obj", &(model[idx]));
				}
			}
			else
			{
				loader->load(modelPath, &(model[0]));
			}

			if (texturePath != "") {
				this->texture = shared_ptr<Image>(
					new Image(texturePath));
			}
			this->initPropVectors();

			if (boundingBoxesPath != "") {
				boundingBoxes = shared_ptr<BoundingBoxes>(new BoundingBoxes());
				boundingBoxes->loadFromFile(boundingBoxesPath);
			}

	}

	SceneObject::~SceneObject() {
		delete[] model;

	}

	Model& SceneObject::getModel() const {
		return model[currentFrame];
	}

	const shared_ptr<Image>& SceneObject::getTexture() const {
		return texture;
	}

	const string SceneObject::getName()
	{
		return name;
	}

	const shared_ptr<glm::vec4>& SceneObject::getColour() {
		return colour;
	}

	void SceneObject::setColour(const float &r, const float &g, const float &b, const float &a) {
		colour = shared_ptr<glm::vec4>(new glm::vec4(r, g ,b, a));
	}

	const shared_ptr<glm::vec3>& SceneObject::getOffset() const {
		return offset;
	}

	void SceneObject::setOffset(const float &x, const float &y, const float &z) {
		offset = shared_ptr<glm::vec3>(new glm::vec3(x, y ,z));
	}

	const shared_ptr<glm::vec3>& SceneObject::getRotation() const {
		return rotation;
	}

	void SceneObject::setRotation(const float &x, const float &y,
		const float &z) {
			rotation = shared_ptr<glm::vec3>(new glm::vec3(x, y ,z));
	}

	void SceneObject::startAnimating()
	{
		animating = true;
	}

	void SceneObject::stopAnimating()
	{
		animating = false;
	}

	void SceneObject::resetAnimation()
	{
		currentFrame = 0;
	}

	void SceneObject::setFrameDelay( const int &delay )
	{
		this->frameDelay = delay;
	}

	void SceneObject::animate()
	{
		if(animating) {
			++framesWaited;
			if (framesWaited == frameDelay) {
				framesWaited = 0;
				++currentFrame;
				if (currentFrame == numFrames) {
					currentFrame = 0;
				}
			}
		}
	}

	bool SceneObject::collidesWithPoint( float x, float y, float z )
	{
		if (boundingBoxes == NULL) {
			throw Exception("No bounding boxes have been provided for " + name + ", so collision detection is not enabled.");
		}

		return boundingBoxes->pointCollides(x, y, z, offset->x, offset->y, offset->z, rotation->y);
	}

	bool SceneObject::collidesWithSceneObject( shared_ptr<SceneObject> otherObject )
	{
		if (boundingBoxes == NULL) {
			throw Exception("No bounding boxes have been provided for " + name + ", so collision detection is not enabled.");
		}

		if (otherObject->boundingBoxes == NULL) {
			throw Exception("No bounding boxes have been provided for " + otherObject->name + ", so collision detection is not enabled.");
		}

		return boundingBoxes->boxesCollide(otherObject->boundingBoxes, otherObject->offset->x, otherObject->offset->y,
			otherObject->offset->z, otherObject->rotation->y, offset->x, offset->y, offset->z, rotation->y);

	}

}

