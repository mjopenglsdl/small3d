/*
*  GameLogic.h
*
*  Created on: 2014/11/09
*      Author: Dimitri Kourkoulis
*              http://dimitros.be
*     License: MIT
*/

#pragma once

#include <memory>
#include <dimitrikourk/small3d/Configuration.h>
#include <dimitrikourk/small3d/Logger.h>
#include <dimitrikourk/small3d/SceneObject.h>
#include <dimitrikourk/small3d/Scene.h>

#include <dimitrikourk/small3d/samplegame/KeyInput.h>

using namespace small3d;

namespace AvoidTheBug3D {

	class GameLogic {

	private:

		shared_ptr<Configuration> cfg;
		shared_ptr<Logger> log;

		shared_ptr<SceneObject> goat;
		shared_ptr<SceneObject> bug;
		shared_ptr<SceneObject> tree;

		enum GameState {START_SCREEN, PLAYING};
		GameState gameState;

		enum BugState {FLYING_STRAIGHT, TURNING, DIVING_DOWN, DIVING_UP};
		BugState bugState, bugPreviousState;
		int bugFramesInCurrentState;
		float bugVerticalSpeed;

		void initGame();
		void processGame(const KeyInput &keyInput);
		void processStartScreen(const KeyInput &keyInput);

		void moveGoat(const KeyInput &keyInput);
		void moveBug();
		
	public:

		/**
		 * @brief	The game scene.
		 */
		shared_ptr<Scene> gameScene;

		/**
		 * Constructor
		 * @param	cfg	The game's configuration object.
		 * @param	log	The game's logging object.
		 */
		GameLogic(const shared_ptr<Configuration> cfg,
			const shared_ptr<Logger> log);

		/**
		* Destructor
		*/
		~GameLogic();

		/**
		 * Process conditions and set up the next frame, also taking into consideration
		 * the input from the keyboard
		 * 
		 * @param	keyInput	The keyboard input
		 */
		void process(const KeyInput &keyInput);
	};

} /* namespace AvoidTheBug3D */

