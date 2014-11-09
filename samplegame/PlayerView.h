/*
*  PlayerView.h
*
*  Created on: 2014/11/09
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

#ifndef PLAYERVIEW_H_
#define PLAYERVIEW_H_

#include <memory>
#include <dimitrikourk/small3d/Logger.h>
#include <dimitrikourk/small3d/SceneObject.h>
#include <dimitrikourk/small3d/Renderer.h>
#include <dimitrikourk/small3d/Scene.h>

using namespace small3d;

namespace AvoidTheBug3D {

	class PlayerView {

	private:
	
		shared_ptr<Renderer> renderer;

	public:

		/**
		* Constructor
		*/
		PlayerView();

		/**
		* Destructor
		*/
		~PlayerView();

		/**
		 * Renders the given scene
		 *
		 * @param	scene	The scene
		 */
		void render(shared_ptr<Scene> gameScene);
	};

} /* namespace AvoidTheBug3D */

#endif /* PLAYERVIEW_H_ */
