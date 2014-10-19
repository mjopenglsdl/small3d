/*
*  Scene.cpp
*
*  Created on: 2014/10/19
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: GNU LGPL
*/

#include "Scene.h"

namespace small3d {

	Scene::Scene(const shared_ptr<Configuration> cfg,
		const shared_ptr<EngineLog> log){

			this->cfg = cfg;
			this->log = log;

			showingStartScreen = true;

			sceneObjects = shared_ptr<vector<shared_ptr<SceneObject> > >(
				new vector<shared_ptr<SceneObject> >());
	}

	Scene::~Scene() {

	}
}