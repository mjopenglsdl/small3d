/*
 *  Image.cpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "Image.hpp"
#include "Exception.hpp"
#include "MathFunctions.hpp"
#include "SDL.h"


using namespace std;

namespace small3d {

  Image::Image(const string &fileLocation) {
    initLogger();
    width = 0;
    height = 0;

    imageData = nullptr;
    imageDataSize=0;

    this->loadFromFile(fileLocation);

  }

  Image::Image(const Image &other) {
    width = other.width;
    height = other.height;
    imageDataSize = other.imageDataSize;
    imageData = new float[imageDataSize];
    copy(other.imageData, other.imageData + imageDataSize, imageData);
  }

  Image::Image(Image &&other) noexcept: imageData(other.imageData) {
    width = other.width;
    height = other.height;
    imageDataSize = other.imageDataSize;
    other.width = 0;
    other.height = 0;
    other.imageDataSize = 0;
    other.imageData = nullptr;
  }

  Image& Image::operator= (const Image& other) {
    Image tmp(other);
    *this = std::move(tmp);
    return *this;
  }

  Image& Image::operator= (Image&& other) noexcept {
    if(imageData != nullptr)
      delete[] imageData;
    imageData = other.imageData;
    other.imageData = nullptr;
    return *this;
  }

  Image::~Image() {

    if (imageData != nullptr) {
      delete[] imageData;
    }
  }

  void Image::loadFromFile(const string &fileLocation) {
    // function developed based on example at
    // http://zarb.org/~gc/html/libpng.html
#if defined(_WIN32) && !defined(__MINGW32__)
    FILE *fp;
    fopen_s(&fp, (SDL_GetBasePath() + fileLocation).c_str(), "rb");
#else
    FILE *fp = fopen((SDL_GetBasePath() + fileLocation).c_str(), "rb");
#endif
    if (!fp) {
      throw Exception(
        "Could not open file " + string(SDL_GetBasePath())
        + fileLocation);
    }

    png_infop pngInformation = nullptr;
    png_structp pngStructure = nullptr;
    png_byte colorType;
    png_bytep *rowPointers = nullptr;

    unsigned char header[8]; // Using maximum size that can be checked

    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8)) {
      throw Exception(
        "File " + string(SDL_GetBasePath()) + fileLocation
        + " is not recognised as a PNG file.");
    }

    pngStructure = png_create_read_struct(PNG_LIBPNG_VER_STRING,
      nullptr, nullptr, nullptr);

    if (!pngStructure) {
      fclose(fp);
      throw Exception("Could not create PNG read structure.");
    }

    pngInformation = png_create_info_struct(pngStructure);

    if (!pngInformation) {
      png_destroy_read_struct(&pngStructure, nullptr, nullptr);
      fclose(fp);
      throw Exception("Could not create PNG information structure.");
    }

    if (setjmp(png_jmpbuf(pngStructure))) {
      png_destroy_read_struct(&pngStructure, &pngInformation, nullptr);
      pngStructure = nullptr;
      pngInformation = nullptr;
      fclose(fp);
      throw Exception("PNG read: Error calling setjmp. (1)");
    }

    png_init_io(pngStructure, fp);
    png_set_sig_bytes(pngStructure, 8);

    png_read_info(pngStructure, pngInformation);

    width = static_cast<int>(png_get_image_width(pngStructure, pngInformation));
    height = static_cast<int>(png_get_image_height(pngStructure, pngInformation));

    colorType = png_get_color_type(pngStructure, pngInformation);
    png_set_interlace_handling(pngStructure);

    png_read_update_info(pngStructure, pngInformation);

    if (setjmp(png_jmpbuf(pngStructure))) {
      png_destroy_read_struct(&pngStructure, &pngInformation, nullptr);
      pngStructure = nullptr;
      pngInformation = nullptr;
      fclose(fp);
      throw Exception("PNG read: Error calling setjmp. (2)");
    }

    rowPointers = new png_bytep[sizeof(png_bytep) * height];

    for (int y = 0; y < height; y++) {
      rowPointers[y] = new png_byte[png_get_rowbytes(pngStructure,
        pngInformation)];
    }

    png_read_image(pngStructure, rowPointers);

    if (colorType != PNG_COLOR_TYPE_RGB) {
      throw Exception(
        "For now, only RGB png images are supported, with no transparency information saved.");
    }

    imageDataSize = (unsigned int) (4 * width * height);

    imageData = new float[imageDataSize];

    for (int y = 0; y < height; y++) {

      png_byte *row = rowPointers[y];

      for (int x = 0; x < width; x++) {

        png_byte *ptr = &(row[x * 3]);

        float rgb[3];

        rgb[0] = static_cast<float>(ptr[0]);
        rgb[1] = static_cast<float>(ptr[1]);
        rgb[2] = static_cast<float>(ptr[2]);

        imageData[y * width * 4 + x * 4] = ROUND_2_DECIMAL(rgb[0] / 255.0f);
        imageData[y * width * 4 + x * 4 + 1] = ROUND_2_DECIMAL(rgb[1] / 255.0f);
        imageData[y * width * 4 + x * 4 + 2] = ROUND_2_DECIMAL(rgb[2] / 255.0f);
        imageData[y * width * 4 + x * 4 + 3] = 1.0f;

      }
    }

    fclose(fp);

    for (int y = 0; y < height; y++) {
      delete[] rowPointers[y];
    }
    delete[] rowPointers;

    if (pngInformation != nullptr || pngStructure != nullptr) {
      png_destroy_read_struct(&pngStructure, &pngInformation, nullptr);
      pngStructure = nullptr;
      pngInformation = nullptr;
    }
  }

  int Image::getWidth() const {
    return width;
  }

  int Image::getHeight() const {
    return height;
  }

  unsigned int Image::size() const {
    return imageDataSize;
  }

  float *Image::getData() const {
    return imageData;
  }

}
