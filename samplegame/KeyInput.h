#pragma once

/*
* KeyInput.h
*
*  Created on: 23 Sept 2014
*      Author: Dimitri Kourkoulis
*/

#ifndef KEYINPUT_H_
#define KEYINPUT_H_

namespace AvoidTheBug3D
{
	/**
	 * @typedef	struct KeyInput
	 *
	 * @brief	Structure holding the state of keys on the keyboard that are related to the game.
	 */

	typedef struct KeyInput  
	{
		bool up, down, left, right, enter;

		KeyInput()
		{
			up = false;
			down = false;
			left = false;
			right = false;
			enter = false;
		}

	} KeyInput;

}

#endif