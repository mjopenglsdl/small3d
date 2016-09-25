/*
 *  Image.hpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <string>
#include <memory>
#include <vector>
#include "Logger.hpp"
#include <png.h>

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
    vector<float> imageData;
    unsigned int imageDataSize;

    void loadFromFile(const string &fileLocation);

  public:

    /**
     * Default constructor
     * @param fileLocation Location of image file
     */
    Image(string fileLocation = "");

    /**
     * Destructor
     */
    ~Image() = default;

    /**
     * Get the image width
     * @return The image width
     */
    const int getWidth() const;

    /**
     * Get the image height
     * @return The image height
     */
    const int getHeight() const;

    /**
     * Get the size of the image, in bytes
     * @return Size of the image, in bytes
     */
    const unsigned int size() const;

    /**
     * Get the image data
     * @return The image data
     */
    const float* getData() const;

  };

}
