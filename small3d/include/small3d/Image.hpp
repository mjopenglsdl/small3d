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
    float* imageData;
    unsigned int imageDataSize;

    void loadFromFile(const string &fileLocation);

  public:

    Image() = delete;

    /**
     * Constructor
     * @param fileLocation Location of image file
     */
    Image(const string &fileLocation);

    /**
     * Copy constructor
     * @param other The other image
     */
    Image(const Image &other);

    /**
     * Move constructor
     * @param other
     */
    Image(Image &&other) noexcept ;

    /**
     * Copy assignment operator
     * @param other Other image
     * @return This image
     */
    Image& operator= (const Image& other);

    /**
     * Move assignment operator
     * @param other Other image
     * @return This image
     */
    Image& operator= (Image&& other) noexcept;

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
     * Get the size of the image, in bytes
     * @return Size of the image, in bytes
     */
    unsigned int size() const;

    /**
     * Get the image data
     * @return The image data
     */
    float* getData() const;

  };

}
