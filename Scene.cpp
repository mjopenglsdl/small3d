/*
*  Scene.cpp
*
*  Created on: 2014/10/19
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

#include "Scene.h"

namespace small3d {

	Scene::Scene(const shared_ptr<Configuration> cfg,
		const shared_ptr<Logger> log){

			this->cfg = cfg;
			this->log = log;

			showingStartScreen = true;

			sceneObjects = shared_ptr<vector<shared_ptr<SceneObject> > >(
				new vector<shared_ptr<SceneObject> >());
	}

	Scene::~Scene() {

	}
}