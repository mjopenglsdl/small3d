/*
 *  SoundData.cpp
 *
 *  Created on: 2014-12-21
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#include "SoundData.hpp"

namespace small3d {

  SoundData::SoundData(){
  }

  SoundData::~SoundData(){
    if (data) {
      delete[] data;
    }
  }

}
