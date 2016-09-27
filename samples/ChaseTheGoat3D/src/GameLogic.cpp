/*
 *  GameLogic.cpp
 *
 *  Created on: 2014/11/09
 *      Author: Dimitri Kourkoulis
 *     License: BSD 3-Clause License (see LICENSE file)
 */


#define MAX_Z -1.0f
#define MIN_Z -24.0f

#define GROUND_Y -1.0f
#define FULL_ROTATION 6.28f // More or less 360 degrees in radians

#define BUG_TILT_SPEED 0.03f
#define BUG_ROTATION_SPEED 0.06f
#define BUG_SPEED 0.08f
#define BUG_START_ALTITUDE 2.6f

#define GOAT_ROTATION_SPEED 0.1f
#define GOAT_SPEED 0.05f

#include <memory>
#include <small3d/MathFunctions.hpp>
#include <small3d/Exception.hpp>
#include "GameLogic.hpp"


using namespace small3d;

namespace AvoidTheBug3D {

  GameLogic::GameLogic() :
      renderer(854, 480, false, "Chase the Goat 3D"),
      goat("goat", "resources/models/Goat/goatAnim",
           19, "resources/models/Goat/Goat.png",
           "resources/models/GoatBB/GoatBB.obj"),
      bug("bug", "resources/models/Bug/bugAnim", 9),
      tree("tree",
           "resources/models/Tree/tree.obj",
           1, "resources/models/Tree/tree.png",
           "resources/models/TreeBB/TreeBB.obj")
  {

    Image startScreenTexture("resources/images/startScreen.png");

    renderer.generateTexture("startScreen", startScreenTexture.getData(), startScreenTexture.getWidth(),
                             startScreenTexture.getHeight());

    Image groundTexture("resources/images/grass.png");
    renderer.generateTexture("ground", groundTexture.getData(), groundTexture.getWidth(), groundTexture.getHeight());

    Image skyTexture("resources/images/sky.png");
    renderer.generateTexture("sky", skyTexture.getData(), skyTexture.getWidth(), skyTexture.getHeight());


    bug.colour = glm::vec4(0.2f, 0.2f, 0.2f, 1.0f);
    bug.setFrameDelay(2);

    tree.offset = glm::vec3(2.6f, GROUND_Y, -8.0f);
    tree.rotation = glm::vec3(0.0f, -0.5f, 0.0f);

    gameState = START_SCREEN;
	
    sound.load("resources/sounds/bah.ogg", "bah");

    startTicks = 0;
    seconds = 0;

    lightModifier = -0.01f;
  }

  void GameLogic::initGame()
  {
    goat.offset = glm::vec3(-1.2f, GROUND_Y, -4.0f);
    bug.offset = glm::vec3(3.6f, GROUND_Y + BUG_START_ALTITUDE, -5.0f);

    bug.startAnimating();

    startTicks = SDL_GetTicks();

  }

  void GameLogic::moveGoat()
  {
    goat.animate();

  }

  void GameLogic::moveBug(const KeyInput &keyInput)
  {

    if (keyInput.left) {
      bug.rotation.y -= BUG_ROTATION_SPEED;

      if (bug.rotation.y < -FULL_ROTATION)
        bug.rotation.y = 0.0f;


    }
    else if (keyInput.right) {
      bug.rotation.y += BUG_ROTATION_SPEED;

      if (bug.rotation.y > FULL_ROTATION)
        bug.rotation.y = 0.0f;


    }

    if (keyInput.up) {

      bug.rotation.z -= BUG_TILT_SPEED;

      if (bug.rotation.z < -0.75f)
        bug.rotation.z = -0.75f;


    }
    else if (keyInput.down) {

      bug.rotation.z += BUG_TILT_SPEED;

      if (bug.rotation.z > 0.75f)
        bug.rotation.z = 0.75f;
    }

    if (keyInput.space) {
      bug.offset.x -= cos(bug.rotation.y) * BUG_SPEED;
      bug.offset.z -= sin(bug.rotation.y) * BUG_SPEED;
      bug.offset.y += sin(bug.rotation.z) * BUG_SPEED;
    }
	
    if (bug.offset.y < GROUND_Y + 0.5f)
      bug.offset.y = GROUND_Y + 0.5f;

	  // Looking through the eyes of the bug
    renderer.cameraPosition = bug.offset;
    renderer.cameraRotation = bug.rotation;
	
    bug.animate();

    if (goat.collidesWith(bug.offset.x, bug.offset.y, bug.offset.z))
    {
      gameState = START_SCREEN;
      sound.play("bah");
    }
  }

  void GameLogic::processGame(const KeyInput &keyInput)
  {
    moveBug(keyInput);
    moveGoat();
  }

  void GameLogic::processStartScreen(const KeyInput &keyInput)
  {
    if (keyInput.enter) {
      initGame();
      gameState = PLAYING;
    }
  }

  void GameLogic::process(const KeyInput &keyInput)
  {
    switch (gameState) {
    case START_SCREEN:
      processStartScreen(keyInput);
      break;
    case PLAYING:
      processGame(keyInput);
      break;
    default:
      throw Exception("Urecognised game state");
    }
  }

  void GameLogic::render()
  {
    renderer.clearScreen();

    //Uncomment for groovy nightfall effect :)
    /* renderer.lightIntensity += lightModifier;

      if (renderer.lightIntensity < 0)
      {
      renderer.lightIntensity = 0.0f;
      lightModifier = 0.01f;
      }

      if (renderer.lightIntensity > 1.0f)
      {
      renderer.lightIntensity = 1.0f;
      lightModifier = -0.01f;
      } */

    if (gameState == START_SCREEN) {
      float startScreenVerts[16] =
      {
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f
      };

      renderer.render(&startScreenVerts[0], "startScreen");

      if (seconds != 0)
      {
        SDL_Color textColour = { 255, 100, 0, 255 };
        renderer.render("Goat not bitten for " + intToStr(seconds) + " seconds",
          textColour, -0.95f, -0.6f, 0.0f, -0.8f);
      }

    }
    else
    {

      float skyVerts[16] =
      {
        -1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, -1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 1.0f, 1.0f
      };

      renderer.render(&skyVerts[0], "sky");

      // Draw the background

      float groundVerts[16] =
      {
        -25.0f, GROUND_Y, MAX_Z, 1.0f,
        25.0f, GROUND_Y, MAX_Z, 1.0f,
        25.0f, GROUND_Y,  MIN_Z, 1.0f,
        -25.0f, GROUND_Y, MIN_Z, 1.0f
      };

      renderer.render(&groundVerts[0], "ground", true, glm::vec3(0.0f, 0.0f, 0.0f));

      renderer.render(goat);
      renderer.render(bug);
      renderer.render(tree);

    }
    renderer.swapBuffers();
  }

}
