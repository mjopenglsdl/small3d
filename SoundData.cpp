/*
 *  SoundData.cpp
 *
 *  Created on: 2014-12-21
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "SoundData.hpp"
#include <cstring>

namespace small3d {

  SoundData::SoundData(){
    channels = 0;
    rate = 0;
    samples = 0;
    size = 0;
    duration = 0.0;
    startTime = 0.0;

    currentFrame = 0;

    data = NULL;
  }

  SoundData::~SoundData(){
    if (data) {
      delete[] data;
    }
  }

}
