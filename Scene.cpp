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

	Scene::Scene(){
			initLogger();

			showingStartScreen = true;

			sceneObjects = shared_ptr<vector<shared_ptr<SceneObject> > >(
				new vector<shared_ptr<SceneObject> >());
	}

	Scene::~Scene() {

	}
}