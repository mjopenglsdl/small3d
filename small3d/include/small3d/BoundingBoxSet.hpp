/*
 *  BoundingBoxSet.hpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <memory>
#include "Logger.hpp"
#include <vector>
#include <glm/glm.hpp>

using namespace std;

namespace small3d {

  /**
   * @class BoundingBoxSet
   * @brief Bounding boxes for a model. Even though the loading logic is similar
   * to that of the Model class, BoundingBoxSet is a separate class with
   * a separate loading function, because it loads a Wavefront file
   * exported with a different set of options (see README.md).
   * Each BoundingBoxSet class may contain more than one bounding boxes,
   * which means that it is a set of bounding boxes. These are
   * not separated into different structures because each has a set of
   * six faces and this fact can be used to separate them at runtime.
   */

  class BoundingBoxSet {
  private:

    int numBoxes;

  public:

    /**
     * @brief The offset of the set of bounding boxes (their position on the scene).
     */

    glm::vec3 offset;

    /**
     * @brief The roation (around the x, y and z axes) of the set of bounding boxes.
     */

    glm::vec3 rotation;

    /**
     * @brief Constructor
     */

    BoundingBoxSet();

    /**
     * @brief Destructor
     */
    ~BoundingBoxSet() = default;

    /**
     * @brief Vertex coordinates read from Wavefront .obj file
     */

    vector<vector<float> > vertices;

    /**
     * @brief Faces vertex indexes read from Wavefront .obj file
     */

    vector<vector<int> > facesVertexIndexes;

    /**
     * @brief Load the bounding boxes from a Wavefront file.
     *
     * @param	fileLocation	The file location, relative to the game's
     * 							execution directory
     */

    void loadFromFile(string fileLocation);

    /**
     * @brief Check if a point collides (or is inside) any of the boxes
     * assuming that they are in a given offset and have a certain rotation.
     *
     * @param	point		 	The point (as a vector)
     *
     * @return	true if there is a collision, false if not.
     */

    bool collidesWith(glm::vec3 point) const;

    /**
     * @brief Check if another set of bounding boxes is located with this set (even partially), 
     * thus colliding with it.
     *
     * @param otherBoxSet The other box set
     *
     * @return	true if there is a collision, false if not.
     */

    bool collidesWith(BoundingBoxSet &otherBoxSet) const;

  };
}
