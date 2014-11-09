/*
*  Scene.h
*
*  Created on: 2014/10/19
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

#pragma once

#include <memory>
#include "Logger.h"
#include "SceneObject.h"

namespace small3d {

	/**
	* @struct	Scene
	*
	* @brief	The game scene
	*
	*/

	struct Scene
	{
	public:

		/**
		 * @brief	Showing start screen.
		 */
		bool showingStartScreen;

		/**
		 * The set of scene objects, in their current state.
		 *
		 * @return	The scene objects.
		 */
		shared_ptr<vector<shared_ptr<SceneObject> > > sceneObjects;

		/**
		* Constructor
		*/
		Scene();

		/**
		* Destructor
		*/
		~Scene();
	};

}
