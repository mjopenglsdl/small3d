/*
 *  Image.hpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <string>
#include <memory>
#include "Logger.hpp"
#include <glenn/png/png.h>

using namespace std;

namespace small3d {

  /**
   * @class	Image
   *
   * @brief	Image loading class. Only handles RGB encoded data in PNG files for now.
   *
   */

  class Image {
  private:

    int width, height;
    float* imageData;

    // Load image from a .png file
    void loadFromFile(const string &fileLocation);

  public:
    /**
     * Constructor
     * @param fileLocation Location of image file
     */
    Image(const string &fileLocation);

    /**
     * Destructor
     */
    ~Image();

    /**
     * Get the image width
     * @return The image width
     */
    int getWidth() const;

    /**
     * Get the image height
     * @return The image height
     */
    int getHeight() const;

    /**
     * Get the image data
     * @return The image data
     */
    float* getData() const;

  };

}
