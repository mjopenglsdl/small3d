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
#include <stdexcept>
#include "WavefrontLoader.hpp"
#include "MathFunctions.hpp"


using namespace std;

namespace small3d {

  template<class LoaderType> SceneObject<LoaderType>::SceneObject<LoaderType>(string name, string modelPath, int numFrames, string texturePath,
                           string boundingBoxSetPath) : texture(texturePath),
									colour(0,0,0,0), offset(0,0,0),
							rotation(0,0,0), boundingBoxSet(boundingBoxSetPath) {
    initLogger();
    this->name = name;
    animating = false;
    framesWaited = 0;
    frameDelay = 1;
    currentFrame = 0;
    this->numFrames = numFrames;

    LoaderType loader;

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

  }

  template<class LoaderType> Model& SceneObject<LoaderType>::getModel() {
    return model[currentFrame];
  }

  template<class LoaderType> const Image& SceneObject<LoaderType>::getTexture() const {
    return texture;
  }

  template<class LoaderType> const string SceneObject<LoaderType>::getName() {
    return name;
  }

  template<class LoaderType> void SceneObject<LoaderType>::adjustRotation(const glm::vec3 &adjustment) {
    rotationAdjustment = rotateZ(adjustment.z) * rotateX(adjustment.x) * rotateY(adjustment.y);
    if (boundingBoxSet.vertices.size() > 0)
      boundingBoxSet.setRotationAdjustment(rotationAdjustment);
  }

  template<class LoaderType> const glm::mat4x4 &SceneObject<LoaderType>::getRotationAdjustment() {
    return rotationAdjustment;
  }

  template<class LoaderType> void SceneObject<LoaderType>::startAnimating() {
    animating = true;
  }

  template<class LoaderType> void SceneObject<LoaderType>::stopAnimating() {
    animating = false;
  }

  template<class LoaderType> void SceneObject<LoaderType>::resetAnimation() {
    currentFrame = 0;
  }

  template<class LoaderType> void SceneObject<LoaderType>::setFrameDelay(const int &delay) {
    this->frameDelay = delay;
  }

  template<class LoaderType> void SceneObject<LoaderType>::animate() {
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

  template<class LoaderType> bool SceneObject<LoaderType>::collidesWith(glm::vec3 point) {
    if (boundingBoxSet.vertices.size() == 0) {
      throw runtime_error("No bounding boxes have been provided for " + name + ", so collision detection is not enabled.");
    }

    boundingBoxSet.offset = this->offset;
    boundingBoxSet.rotation = this->rotation;

    return boundingBoxSet.collidesWith(point);
  }

  template<class LoaderType> bool SceneObject<LoaderType>::collidesWith(SceneObject &otherObject) {
    if (boundingBoxSet.vertices.size() == 0) {
      throw runtime_error("No bounding boxes have been provided for " + name + ", so collision detection is not enabled.");
    }

    if (otherObject.boundingBoxSet.vertices.size() == 0) {
      throw runtime_error(
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

  template<class LoaderType> bool SceneObject<LoaderType>::isAnimated() {
    return numFrames > 1;
  }

}
