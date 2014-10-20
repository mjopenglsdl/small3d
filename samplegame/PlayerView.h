/*
* PlayerView.h
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

#ifndef PLAYERVIEW_H_
#define PLAYERVIEW_H_

#include <memory>
#include <dimitrikourk/small3d/Configuration.h>
#include <dimitrikourk/small3d/EngineLog.h>
#include <dimitrikourk/small3d/SceneObject.h>
#include <dimitrikourk/small3d/Renderer.h>
#include <dimitrikourk/small3d/Scene.h>

using namespace small3d;

namespace AvoidTheBug3D {

	class PlayerView {

	private:
		shared_ptr<Configuration> cfg;
		shared_ptr<EngineLog> log;

		shared_ptr<Renderer> renderer;

	public:

		/**
		* Constructor
		* @param cfg The game's configuration object
		* @param log The game's logging object
		*/
		PlayerView(const shared_ptr<Configuration> cfg,
			const shared_ptr<EngineLog> log);

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
