/*
 *  Image.cpp
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "Image.hpp"
#include <stdio.h>
#include "Exception.hpp"
#include "MathFunctions.hpp"
#include <miguel/sdl2/include/SDL.h>

using namespace std;

namespace small3d {

  Image::Image(const string &fileLocation) {
    initLogger();
    width = 0;
    height = 0;

    imageData = NULL;

    this->loadFromFile(fileLocation);

  }

  Image::~Image() {

    if (imageData != NULL) {
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

    png_infop pngInformation = NULL;
    png_structp pngStructure = NULL;
    png_byte colorType = static_cast<png_byte>(0);
    png_byte bitDepth = static_cast<png_byte>(0);
    int numberOfPasses = 0;
    png_bytep *rowPointers = NULL;

    unsigned char header[8]; // Using maximum size that can be checked

    fread(header, 1, 8, fp);

    if (png_sig_cmp(header, 0, 8)) {
      throw Exception(
        "File " + string(SDL_GetBasePath()) + fileLocation
        + " is not recognised as a PNG file.");
    }

    pngStructure = png_create_read_struct(PNG_LIBPNG_VER_STRING,
      NULL, NULL, NULL);

    if (!pngStructure) {
      fclose(fp);
      throw Exception("Could not create PNG read structure.");
    }

    pngInformation = png_create_info_struct(pngStructure);

    if (!pngInformation) {
      png_destroy_read_struct(&pngStructure, NULL, NULL);
      fclose(fp);
      throw Exception("Could not create PNG information structure.");
    }

    if (setjmp(png_jmpbuf(pngStructure))) {
      png_destroy_read_struct(&pngStructure, &pngInformation, NULL);
      pngStructure = NULL;
      pngInformation = NULL;
      fclose(fp);
      throw Exception("PNG read: Error calling setjmp. (1)");
    }

    png_init_io(pngStructure, fp);
    png_set_sig_bytes(pngStructure, 8);

    png_read_info(pngStructure, pngInformation);

    width = static_cast<int>(png_get_image_width(pngStructure, pngInformation));
    height = static_cast<int>(png_get_image_height(pngStructure, pngInformation));

    colorType = static_cast<png_byte>(png_get_color_type(pngStructure, pngInformation));
    bitDepth = static_cast<png_byte>(png_get_bit_depth(pngStructure, pngInformation));
    numberOfPasses = static_cast<int>(png_set_interlace_handling(pngStructure));

    png_read_update_info(pngStructure, pngInformation);

    if (setjmp(png_jmpbuf(pngStructure))) {
      png_destroy_read_struct(&pngStructure, &pngInformation, NULL);
      pngStructure = NULL;
      pngInformation = NULL;
      fclose(fp);
      throw Exception("PNG read: Error calling setjmp. (2)");
    }

    rowPointers = new png_bytep[sizeof(png_bytep) * height];

    for (int y = 0; y < height; y++) {
      rowPointers[y] = new png_byte[png_get_rowbytes(pngStructure,
        pngInformation)];
    }

    png_read_image(pngStructure, rowPointers);

    if (png_get_color_type(pngStructure, pngInformation) != PNG_COLOR_TYPE_RGB) {
      throw Exception(
        "For now, only PNG_COLOR_TYPE_RGB is supported for PNG images.");
    }

    imageData = new float[4 * width * height];

    for (int y = 0; y < height; y++) {

      png_byte *row = rowPointers[y];

      for (int x = 0; x < width; x++) {

        png_byte *ptr = &(row[x * 3]);

        float rgb[3];

        rgb[0] = static_cast<float>(ptr[0]); 
        rgb[1] = static_cast<float>(ptr[1]);
        rgb[2] = static_cast<float>(ptr[2]);

        imageData[y * width * 4 + x * 4] = static_cast<float>(ROUND_2_DECIMAL(rgb[0] / 255.0f));
        imageData[y * width * 4 + x * 4 + 1] = static_cast<float>(ROUND_2_DECIMAL(rgb[1] / 255.0f));
        imageData[y * width * 4 + x * 4 + 2] = static_cast<float>(ROUND_2_DECIMAL(rgb[2] / 255.0f));
        imageData[y * width * 4 + x * 4 + 3] = 1.0f;

      }
    }

    fclose(fp);

    for (int y = 0; y < height; y++) {
      delete[] rowPointers[y];
    }
    delete[] rowPointers;

    if (pngInformation != NULL || pngStructure != NULL) {
      png_destroy_read_struct(&pngStructure, &pngInformation, NULL);
      pngStructure = NULL;
      pngInformation = NULL;
    }
  }

  int Image::getWidth() const {
    return width;
  }

  int Image::getHeight() const {
    return height;
  }

  float *Image::getData() const {
    return imageData;
  }

}
