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

#ifndef SMALL3D_GLFW
#include <SDL.h>
#endif

namespace small3d {

  /**
   * @class	Image
   *
   * @brief	Image loading class. Only handles RGB encoded data in PNG files.
   *
   */

  class Image {
  private:

    unsigned long width, height;
    std::vector<float> imageData;
    unsigned long imageDataSize;
    std::string basePath;
    void loadFromFile(const std::string &fileLocation);

  public:

    /**
     * @brief Default constructor
     *
     * @param fileLocation   Location of image file
     * @param basePath       The path under which all accessed files and directories are
     *                       to be found. If this is not set, it is assumed to be the directory
     *                       containing the application executable when using SDL, or the
     *                       directory from where the execution command is entered when 
     *                       using GLFW.
     */
    Image(std::string fileLocation = "", std::string basePath = "");

    /**
     * @brief Destructor
     */
    ~Image() = default;

    /**
     * @brief Get the image width
     * @return The image width
     */
    unsigned long getWidth() const;

    /**
     * @brief Get the image height
     * @return The image height
     */
    unsigned long getHeight() const;

    /**
     * @brief Get the size of the image, in bytes
     * @return Size of the image, in bytes
     */
    unsigned long size() const;

    /**
     * @brief Get the image data
     * @return The image data
     */
    const float* getData() const;

  };

}
