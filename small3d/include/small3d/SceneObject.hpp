/*
 *  SceneObject.hpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <vector>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <memory>

#include "Model.hpp"
#include "Logger.hpp"
#include "Image.hpp"
#include "BoundingBoxSet.hpp"
#include "MathFunctions.hpp"
#include <glm/glm.hpp>

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

  class SceneObject
  {
  private:
    std::vector<Model> model;
    bool animating;
    int frameDelay;
    int currentFrame;
    int framesWaited;
    int numFrames;
    std::string name;

  public:

    /**
     * @brief Constructor
     *
     * @param name                The name of the object
     * @param modelPath           The path to the file containing the object's model
     * @param numFrames           The number of frames, if the object is animated. A single animation
     * 				  sequence is supported per object and the first frame is considered to
     * 				  be the non-moving state.
     * @param boundingBoxSetPath  The path to the file containing the object's bounding box set. If no such
     * 				  path is given, the object cannot be checked for collision detection.
     */
    SceneObject(std::string name, std::string modelPath, int numFrames = 1, std::string boundingBoxSetPath = "");

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
     * @brief Get the name of the object
     * @return The name of the object
     */
    const std::string getName();

    /**
     * Offset (position) of the object
     */
    glm::vec3 offset;

    /**
     * Rotation of the object (on x, y, z axes respectively)
     */
    glm::vec3 rotation;

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
  
}
