/*
 *  SoundData.h
 *
 *  Created on: 2014-12-21
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

namespace small3d {
  
  /**
   * @struct SoundData
   *
   * @brief Decoded sound data
   */
  struct SoundData {
  public:

    int channels;
    int rate;
    long samples;
    long size;

    char *data;

    /**
     * Default constructor
     */

    SoundData();

    /**
     * Destructor
     */

    ~SoundData();
  };
}
