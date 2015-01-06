/*
 *  BoundingBoxes.hpp
 *
 *  Created on: 2014/10/19
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once
#include <memory>
#include "Logger.hpp"
#include <vector>
#include <dimitrikourk/glm/glm/glm.hpp>

using namespace std;

namespace small3d {

  /**
   * @class	BoundingBoxes
   *
   * @brief	Bounding boxes for a model. Even though the loading logic is similar
   * 			to that of the Model class, BoundingBoxes is a separate class with
   * 			a separate loading function, because it loads a Wavefront file
   * 			exported with a different set of options (see README.md).
   * 			Each BoundingBoxes class may contain more than one bounding boxes,
   *                    which means that it is a set of bounding boxes. These are
   * 			not separated into different structures because each has a set of
   * 			six faces and this fact can be used to separate them at runtime.
   *
   */

  class BoundingBoxes {
  private:

    int numBoxes;

  public:

    /**
     * The offset of the set of bounding boxes (their position on the scene).
     */

    glm::vec3 offset;

    /**
     * The roation (around the x, y and z axes) of the set of bounding boxes.
     */

    glm::vec3 rotation;

    /**
     * Constructor
     */

    BoundingBoxes();

    /**
     * Destructor
     */
    ~BoundingBoxes();

    /**
     * @brief	Vertex coordinates read from Wavefront .obj file
     */

    vector<float*> *vertices;

    /**
     * @brief	Faces vertex indexes read from Wavefront .obj file
     */

    vector<int*> *facesVertexIndexes;

    /**
     * Load the bounding boxes from a Wavefront file.
     * 
     * @param	fileLocation	The file location, relative to the game's
     * 							execution directory
     */

    void loadFromFile(string fileLocation);

    /**
     * Check if a point collides (or is inside) any of the boxes
     * assuming that they are in a given offset and have a certain rotation.
     * The reason the boxes' offset and rotation are passed as parameters is so
     * that there is no need to keep track of them together with the corresponding
     * information of the model they refer to.
     *
     * @param	pointX		 	The point x coordinate.
     * @param	pointY		 	The point y coordinate.
     * @param	pointZ		 	The point z coordinate.
     *
     * @return	true if it succeeds, false if it fails.
     */

    bool pointIsWithin(const float &pointX, const float &pointY, const float &pointZ); 

    /**
     * @fn	bool boxesAreWithin(const BoundingBoxes &otherBoxes, const float &otherBoxesX,
     * 		const float &otherBoxesY, const float &otherBoxesZ, const float &otherBoxesRotation,
     * 		const float &boxesX, const float &boxesY, const float &boxesZ,
     * 		const float &boxesRotation) };
     *
     * @brief	Check if another set of bounding boxes is located with this set (even partly)
     *
     * @return	true if it succeeds, false if it fails.
     */

    bool boxesAreWithin(shared_ptr<BoundingBoxes> otherBoxes);

  };
}
