/*
 *  SceneObject.hpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <vector>
#include "Model.hpp"
#include <memory>
#include "Logger.hpp"
#include "Image.hpp"
#include "BoundingBoxSet.hpp"
#include "WavefrontLoader.hpp"
#include <glm/glm.hpp>

#include <sstream>
#include <iomanip>
#include <stdexcept>
#include "MathFunctions.hpp"

using namespace std;

namespace small3d
{
  /**
   * @class	SceneObject
   *
   * @brief	An object that appears on the 3D scene. It is made up of one or more models (the latter for animation),
   * 			together with information about positioning and rotation and collision detection functionality.
   *
   */

  template <class LoaderType> class SceneObject
  {
  private:
    std::vector<Model> model;
    bool animating;
    int frameDelay;
    int currentFrame;
    int framesWaited;
    int numFrames;
    glm::mat4x4 rotationAdjustment;
    Image texture;
    std::string name;

  public:

    /**
     * @brief Constructor
     *
     * @param name                The name of the object
     * @param modelPath           The path to the file containing the object's model
     * @param texturePath         The path to the file containing the object's texture. If the object
     * 				  is animated, it has to be the path up to the name part of the model.
     * 				  The program will append an underscore, a 6-digit index number and the
     * 				  .obj suffix for each frame. (e.g. goatAnim will become goatAnim_000001.obj,
     * 				  goatAnim_000002.obj, etc.)
     * @param numFrames           The number of frames, if the object is animated. A single animation
     * 				  sequence is supported per object and the first frame is considered to
     * 				  be the non-moving state.
     * @param boundingBoxSetPath  The path to the file containing the object's bounding box set. If no such
     * 				  path is given, the object cannot be checked for collision detection.
     */
    SceneObject<LoaderType>(std::string name, std::string modelPath, int numFrames = 1, std::string texturePath = "",
                std::string boundingBoxSetPath = "");

    /**
     * @brief Destructor
     */
    ~SceneObject() = default;

    /**
     * @brief Get the object's model
     * @return The object's model
     */
    Model& getModel() ;

    /**
     * Is this an animated or a static object (is it associated with more than one frames/models)?
     * @return True if animated, False otherwise.
     */
    bool isAnimated() ;

    /**
     * @brief Get the object's texture
     * @return The object's texture
     */
    const Image& getTexture() const;

    /**
     * @brief Get the name of the object
     * @return The name of the object
     */
    const std::string getName();

    /**
     * Colour of the object (if not mapping a texture)
     */
    glm::vec4 colour;

    /**
     * Offset (position) of the object
     */
    glm::vec3 offset;

    /**
     * Rotation of the object (on x, y, z axes respectively)
     */
    glm::vec3 rotation;

    /**
     * @brief Adjustment of the object's rotation, in case the way it was exported from an editor
     * does not correspond to the way it is supposed to appear in a game.
     * @param adjustment Vector containing the rotation adjustment around the x, y and z axes respectively
     */
    void adjustRotation(const glm::vec3 &adjustment);

    /**
     * @brief Get the matrix that can apply the rotation adjustment for the object (see adjustRotation)
     * @return The rotation adjustment matrix
     */
    const glm::mat4x4& getRotationAdjustment();

    /**
     * @brief Start animating the object
     */
    void startAnimating();

    /**
     * @brief Stop animating the object
     */
    void stopAnimating();

    /**
     * @brief Reset the animation sequence (go to the first frame)
     */
    void resetAnimation();

    /**
     * @brief Set the animation speed
     * @param delay The delay between each animation frame, expressed in number of game frames
     */
    void setFrameDelay(const int &delay);

    /**
     * @brief Process animation (progress current frame if necessary)
     */
    void animate();

    /**
     * @brief	The bounding boxes for the object, used for collision detection.
     */

    BoundingBoxSet boundingBoxSet;

    /**
     * @brief Check if the object collides with a given point
     *
     * @param	point	The point
     *
     * @return	true if a collision is detected, false otherwise.
     */

    bool collidesWith(glm::vec3 point);

    /**
     *
     * @brief	Check if the object collides with another given object.
     *
     * @param	otherObject	The other object.
     *
     * @return	true if there is a collision, false if not.
     */

    bool collidesWith(SceneObject &otherObject);

  };

  template<class LoaderType> SceneObject<LoaderType>::SceneObject(string name, string modelPath, int numFrames, string texturePath,
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
