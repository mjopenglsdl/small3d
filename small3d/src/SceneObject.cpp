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
#include "WavefrontLoader.hpp"
#include "MathFunctions.hpp"


using namespace std;

namespace small3d {

  SceneObject::SceneObject(string name, string modelPath, int numFrames, string texturePath,
                           string boundingBoxSetPath, string basePath) : texture(texturePath),
									colour(0,0,0,0), offset(0,0,0),
									rotation(0,0,0),
									boundingBoxSet(basePath) {
    initLogger();
    this->name = name;
    animating = false;
    framesWaited = 0;
    frameDelay = 1;
    currentFrame = 0;
    this->numFrames = numFrames;

    WavefrontLoader loader(basePath);

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
        loader.load(modelPath + "_" + frameNum + ".obj", model1);
        model.push_back(model1);
      }
    }
    else {
      Model model1;
      loader.load(modelPath, model1);
      model.push_back(model1);
    }

    if (boundingBoxSetPath != "") {
      boundingBoxSet.loadFromFile(boundingBoxSetPath);
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

  void SceneObject::adjustRotation(const glm::vec3 &adjustment) {
    rotationAdjustment = rotateZ(adjustment.z) * rotateX(adjustment.x) * rotateY(adjustment.y);
    if (boundingBoxSet.vertices.size() > 0)
      boundingBoxSet.setRotationAdjustment(rotationAdjustment);
  }

  const glm::mat4x4 &SceneObject::getRotationAdjustment() {
    return rotationAdjustment;
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

  bool SceneObject::collidesWith(glm::vec3 point) {
    if (boundingBoxSet.vertices.size() == 0) {
      throw Exception("No bounding boxes have been provided for " + name + ", so collision detection is not enabled.");
    }

    boundingBoxSet.offset = this->offset;
    boundingBoxSet.rotation = this->rotation;

    return boundingBoxSet.collidesWith(point);
  }

  bool SceneObject::collidesWith(SceneObject &otherObject) {
    if (boundingBoxSet.vertices.size() == 0) {
      throw Exception("No bounding boxes have been provided for " + name + ", so collision detection is not enabled.");
    }

    if (otherObject.boundingBoxSet.vertices.size() == 0) {
      throw Exception(
          "No bounding boxes have been provided for " + otherObject.name + ", so collision detection is not enabled.");
    }

    boundingBoxSet.offset = offset;
    boundingBoxSet.rotation = rotation;

    otherObject.boundingBoxSet.offset = otherObject.offset;
    otherObject.boundingBoxSet.rotation = otherObject.rotation;

    // Checking whether the boxes of this object are within the boxes of the other object or vice versa
    return boundingBoxSet.collidesWith(otherObject.boundingBoxSet) ||
        otherObject.boundingBoxSet.collidesWith(boundingBoxSet);
  }

  bool SceneObject::isAnimated() {
    return numFrames > 1;
  }

}
