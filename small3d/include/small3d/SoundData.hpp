/*
 *  SoundData.hpp
 *
 *  Created on: 2014-12-21
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <unordered_map>
#include <portaudio.h>
#include <vector>


using namespace std;

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

    bool repeat;

    unsigned long currentFrame;

    vector<char> data;

    /**
     * @brief Default constructor
     */

    SoundData() = default;

    /**
     * @brief Destructor
     */

    ~SoundData() = default;
  };
}
