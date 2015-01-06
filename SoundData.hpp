/*
 *  SoundData.hpp
 *
 *  Created on: 2014-12-21
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

namespace small3d {
  
  /**
   * @class SoundData
   *
   * @brief Decoded sound data
   */
  class SoundData {
  public:

    int channels;
    int rate;
    long samples;
    long size;
    double duration;
    double startTime;

    unsigned long currentFrame;

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
