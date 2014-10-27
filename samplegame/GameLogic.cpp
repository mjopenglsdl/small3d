/*
* GameLogic.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

/* bii data directives */
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000001.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000002.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000003.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000004.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000005.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000006.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000007.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000008.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000009.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000010.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000011.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000012.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000013.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000014.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000015.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000016.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000017.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000018.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim_000019.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Goat/Goat.png
// bii://dimitrikourk/small3d/samplegame/resources/models/GoatBB/goatBB.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000001.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000002.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000003.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000004.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000005.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000006.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000007.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000008.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim_000009.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Tree/tree.obj
// bii://dimitrikourk/small3d/samplegame/resources/models/Tree/tree.png

#define MAX_Z -2.0f
#define MIN_Z -24.0f

#define GROUND_Y -1.0f
#define FULL_ROTATION 6.28f // More or less 360 degrees in radians

#define BUG_ROTATION_SPEED 0.12f
#define BUG_DIVE_TILT 0.8f
#define BUG_SPEED 0.08f
#define BUG_DIVE_DURATION 30
#define BUG_START_DIVE_DISTANCE 0.1f
#define BUG_FLIGHT_HEIGHT 1.4f

#define GOAT_ROTATION_SPEED 0.1f
#define GOAT_SPEED 0.05f

#include <memory>
#include <dimitrikourk/small3d/EngineMath.h>
#include <dimitrikourk/small3d/EngineException.h>
#include <dimitrikourk/small3d/EngineMath.h>
#include <cmath>

#include <dimitrikourk/small3d/samplegame/GameLogic.h>

using namespace small3d;

namespace AvoidTheBug3D {

	GameLogic::GameLogic(const shared_ptr<Configuration> cfg,
		const shared_ptr<EngineLog> log) {

			this->cfg = cfg;
			this->log = log;

			gameScene = shared_ptr<Scene>(new Scene(cfg, log));

			goat = shared_ptr<SceneObject> (
				new SceneObject("goat",
				"dimitrikourk/small3d/samplegame/resources/models/Goat/goatAnim",
				cfg, log, 19, "dimitrikourk/small3d/samplegame/resources/models/Goat/Goat.png", 
				"dimitrikourk/small3d/samplegame/resources/models/GoatBB/goatBB.obj"));

			bug = shared_ptr<SceneObject> (
				new SceneObject("bug",
				"dimitrikourk/small3d/samplegame/resources/models/Bug/bugAnim",
				cfg, log, 9));
			bug->setColour(0.2f, 0.2f, 0.2f, 1.0f);
			bug->setFrameDelay(2);

			bugVerticalSpeed = ROUND_2_DECIMAL(BUG_FLIGHT_HEIGHT / BUG_DIVE_DURATION);

			tree = shared_ptr<SceneObject> (
				new SceneObject("tree",
				"dimitrikourk/small3d/samplegame/resources/models/Tree/tree.obj",
				cfg, log, 1, "dimitrikourk/small3d/samplegame/resources/models/Tree/tree.png"));

			tree->setOffset(2.6f, GROUND_Y, -8.0f);
			tree->setRotation(0.0f, -0.5f, 0.0f);

			gameScene->sceneObjects->push_back(goat);
			gameScene->sceneObjects->push_back(bug);
			gameScene->sceneObjects->push_back(tree);

			gameState = START_SCREEN;

	}

	GameLogic::~GameLogic() {
		LOGINFO("GameLogic destructor running");
	}

	void GameLogic::initGame()
	{
		goat->setOffset(-1.2f, GROUND_Y, -4.0f);
		bug->setOffset(0.5f, GROUND_Y + BUG_FLIGHT_HEIGHT, -18.0f);

		bug->startAnimating();

		bugState = FLYING_STRAIGHT;
		bugPreviousState = FLYING_STRAIGHT;
		bugFramesInCurrentState = 1;
	}

	void GameLogic::moveGoat( const KeyInput &keyInput )
	{
		shared_ptr<Vector3> goatRotation = goat->getRotation();
		shared_ptr<Vector3> goatOffset = goat->getOffset();

		goat->stopAnimating();

		if(keyInput.left) {
			goatRotation->y -= GOAT_ROTATION_SPEED;

			if (goatRotation->y < - FULL_ROTATION)
				goatRotation->y = 0.0f;
			goat->startAnimating();

		}
		else if (keyInput.right) {
			goatRotation->y += GOAT_ROTATION_SPEED;

			if (goatRotation->y > FULL_ROTATION)
				goatRotation->y = 0.0f;
			goat->startAnimating();
		}

		if(keyInput.up) {
			float a = 

				goatOffset->x -= cos(goatRotation->y) * GOAT_SPEED;
			goatOffset->z -= sin(goatRotation->y) * GOAT_SPEED;

			if (goatOffset->z < MIN_Z)
				goatOffset->z = MIN_Z;
			if (goatOffset->z > MAX_Z) 
				goatOffset->z = MAX_Z;

			if (goatOffset->x < goatOffset-> z)
				goatOffset->x = goatOffset-> z;
			if (goatOffset->x > -(goatOffset->z)) 
				goatOffset->x = -(goatOffset->z);

			goat->startAnimating();

		}
		else if (keyInput.down) {
			goatOffset->x += cos(goatRotation->y) * GOAT_SPEED;
			goatOffset->z += sin(goatRotation->y) * GOAT_SPEED;

			goat->startAnimating();
		}

		goat->animate();

		goat->setRotation(0.0f, goatRotation->y, 0.0f);

	}

	void GameLogic::moveBug()
	{
		shared_ptr<Vector3> bugRotation = bug->getRotation();
		shared_ptr<Vector3> bugOffset = bug->getOffset();

		float xDistance = bug->getOffset()->x - goat->getOffset()->x;
		float yDistance = bug->getOffset()->z - goat->getOffset()->z;
		float distance = ROUND_2_DECIMAL(sqrt(xDistance * xDistance + yDistance*yDistance));

		float goatRelX = ROUND_2_DECIMAL(xDistance / distance);
		float goatRelY = ROUND_2_DECIMAL(yDistance / distance);

		float bugDirectionX = cos(bug->getRotation()->y);
		float bugDirectionY = sin(bug->getRotation()->y);

		float dotPosDir = goatRelX * bugDirectionX + goatRelY * bugDirectionY; // dot product

		// Bug state: decide
		if (bugState == bugPreviousState) {
			++bugFramesInCurrentState;
		}
		else
		{
			bugFramesInCurrentState = 1;
		}

		bugPreviousState = bugState;

		if (bugState == DIVING_DOWN)
		{
			if (goat->collidesWithPoint(bug->getOffset()->x, bug->getOffset()->y, bug->getOffset()->z))
			{
				gameState = START_SCREEN;
			}

			if (bugFramesInCurrentState > BUG_DIVE_DURATION / 2)
			{
				bugState = DIVING_UP;
			}
		}
		else if (bugState == DIVING_UP)
		{
			if (goat->collidesWithPoint(bug->getOffset()->x, bug->getOffset()->y, bug->getOffset()->z))
			{
				gameState = START_SCREEN;
			}

			if (bugFramesInCurrentState > BUG_DIVE_DURATION / 2) {
				bugState = FLYING_STRAIGHT;
				bugOffset->y = GROUND_Y + BUG_FLIGHT_HEIGHT; // Correction of possible rounding errors
			}
		}
		else
		{

			if (dotPosDir < 0.98f) 
			{
				if (abs(xDistance) > BUG_START_DIVE_DISTANCE)
				{
					bugState = TURNING;
				}
				else
				{
					bugState = FLYING_STRAIGHT;
				}

			}
			else {
				bugState = DIVING_DOWN;
			}

		}

		// Bug state: represent

		bugRotation->z = 0;

		if (bugState == TURNING)
		{

			bugRotation->y -= BUG_ROTATION_SPEED;

		}
		else if (bugState == DIVING_DOWN)
		{
			bugRotation->z = -BUG_DIVE_TILT;
			bugOffset->y -= bugVerticalSpeed;
		}
		else if (bugState == DIVING_UP)
		{
			bugRotation->z = BUG_DIVE_TILT;
			bugOffset->y += bugVerticalSpeed;
		}



		if (bugRotation->y < -FULL_ROTATION)
			bugRotation->y = 0.0f;


		bugOffset->x -= cos(bugRotation->y) * BUG_SPEED;
		bugOffset->z -= sin(bugRotation->y) * BUG_SPEED;

		if (bugOffset->z < MIN_Z)
			bugOffset->z = MIN_Z;
		if (bugOffset->z > MAX_Z) 
			bugOffset->z = MAX_Z;

		if (bugOffset->x < bugOffset-> z)
			bugOffset->x = bugOffset-> z;
		if (bugOffset->x > -(bugOffset->z)) 
			bugOffset->x = -(bugOffset->z);

		bug->animate();
	}

	void GameLogic::processGame( const KeyInput &keyInput )
	{
		moveBug();
		moveGoat(keyInput);
	}

	void GameLogic::processStartScreen( const KeyInput &keyInput )
	{
		gameScene->showingStartScreen = true;
		if (keyInput.enter) {
			initGame();
			gameScene->showingStartScreen = false;
			gameState = PLAYING;
		}
	}

	void GameLogic::process( const KeyInput &keyInput )
	{
		switch(gameState) {
		case START_SCREEN:
			processStartScreen(keyInput);
			break;
		case PLAYING:
			processGame(keyInput);
			break;
		default:
			throw EngineException("Urecognised game state");
			break;
		}
	}

} /* namespace AvoidTheBug3D */
