/*
 *  GetTokens.h
 *
 *  Created on: 2014/10/18
 *      Author: Dimitri Kourkoulis
 *              http://dimitros.be
 *     License: BSD 3-Clause License (see LICENSE file)
 */

#pragma once

#include <string>

using namespace std;

namespace small3d {

  /**
   * Separates a string into tokens, using the given character
   * as a separator
   *
   * @param	input		  	The input string
   * @param	sep			  	The separator
   * @param [in,out]	tokens	The tokens
   *
   * @return	The number of tokens
   */

  int getTokens(string input, char sep, string* tokens);
}
