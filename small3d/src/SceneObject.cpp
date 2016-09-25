/*
 * SceneObject.cpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "SceneObject.hpp"
#include <sstream>
#include <iomanip>
#include "Exception.hpp"
#include "ModelLoader.hpp"
#include "WavefrontLoader.hpp"

using namespace std;

namespace small3d {

  SceneObject::SceneObject(string name, string modelPath, int numFrames, string texturePath,
                           string boundingBoxesPath) : texture(texturePath), colour(0,0,0,0), offset(0,0,0),
                                                       rotation(0,0,0), boundingBoxes() {
    initLogger();
    this->name = name;
    animating = false;
    framesWaited = 0;
    frameDelay = 1;
    currentFrame = 0;
    this->numFrames = numFrames;

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
        Model model1;
        loader->load(modelPath + "_" + frameNum + ".obj", model1);
        model.push_back(model1);
      }
    }
    else {
      Model model1;
      loader->load(modelPath, model1);
      model.push_back(model1);
    }

    if (boundingBoxesPath != "") {
      boundingBoxes.loadFromFile(boundingBoxesPath);
    }

  }

  Model& SceneObject::getModel() {
    return model[currentFrame];
  }

  const Image& SceneObject::getTexture() const {
    return texture;
  }

  const string SceneObject::getName() {
    return name;
  }

  void SceneObject::startAnimating() {
    animating = true;
  }

  void SceneObject::stopAnimating() {
    animating = false;
  }

  void SceneObject::resetAnimation() {
    currentFrame = 0;
  }

  void SceneObject::setFrameDelay(const int &delay) {
    this->frameDelay = delay;
  }

  void SceneObject::animate() {
    if (animating) {
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

  bool SceneObject::collidesWithPoint(float x, float y, float z) {
    if (boundingBoxes.vertices.size() == 0) {
      throw Exception("No bounding boxes have been provided for " + name + ", so collision detection is not enabled.");
    }

    boundingBoxes.offset = this->offset;
    boundingBoxes.rotation = this->rotation;

    return boundingBoxes.pointIsWithin(x, y, z);
  }

  bool SceneObject::collidesWithSceneObject(shared_ptr<SceneObject> otherObject) {
    if (boundingBoxes.vertices.size() == 0) {
      throw Exception("No bounding boxes have been provided for " + name + ", so collision detection is not enabled.");
    }

    if (otherObject->boundingBoxes.vertices.size() == 0) {
      throw Exception(
          "No bounding boxes have been provided for " + otherObject->name + ", so collision detection is not enabled.");
    }

    boundingBoxes.offset = offset;
    boundingBoxes.rotation = rotation;

    otherObject->boundingBoxes.offset = otherObject->offset;
    otherObject->boundingBoxes.rotation = otherObject->rotation;

    // Checking whether the boxes of this object are within the boxes of the other object or vice versa
    return boundingBoxes.boxesAreWithin(otherObject->boundingBoxes) ||
           otherObject->boundingBoxes.boxesAreWithin(boundingBoxes);
  }

}
