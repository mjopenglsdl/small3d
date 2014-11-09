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
#include "Configuration.h"
#include "EngineLog.h"
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
	private:
		shared_ptr<Configuration> cfg;
		shared_ptr<EngineLog> log;
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
		* @param	cfg	The game's configuration object.
		* @param	log	The game's logging object.
		*/
		Scene(const shared_ptr<Configuration> cfg,
			const shared_ptr<EngineLog> log);

		/**
		* Destructor
		*/
		~Scene();
	};

}
