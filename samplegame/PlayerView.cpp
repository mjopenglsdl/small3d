/*
* PlayerView.cpp
*
*  Created on: Dec 26, 2013
*      Author: Dimitri Kourkoulis
*/

/* bii data directives */
// bii://dimitrikourk/small3d/samplegame/resources/images/startScreen.png
// bii://dimitrikourk/small3d/samplegame/resources/images/grass.png
// bii://dimitrikourk/small3d/samplegame/resources/images/sky.png

#include <memory>

#include <dimitrikourk/small3d/samplegame/PlayerView.h>

using namespace small3d;

namespace AvoidTheBug3D {

	PlayerView::PlayerView(const shared_ptr<Configuration> cfg,
		const shared_ptr<EngineLog> log) {

			this->cfg = cfg;
			this->log = log;

			renderer = shared_ptr<Renderer>(new Renderer(cfg, log));
			renderer->init(854, 480, false);

			unique_ptr<Image> startScreenTexture (
				new Image("dimitrikourk/small3d/samplegame/resources/images/startScreen.png", cfg, log));
			renderer->generateTexture("startScreen", startScreenTexture->getData(), startScreenTexture->getWidth(), startScreenTexture->getHeight());

			unique_ptr<Image> groundTexture (
				new Image("dimitrikourk/small3d/samplegame/resources/images/grass.png", cfg, log));
			renderer->generateTexture("ground", groundTexture->getData(), groundTexture->getWidth(), groundTexture->getHeight());

			unique_ptr<Image> skyTexture (
				new Image("dimitrikourk/small3d/samplegame/resources/images/sky.png", cfg, log));
			renderer->generateTexture("sky", skyTexture->getData(), skyTexture->getWidth(), skyTexture->getHeight());

	}

	PlayerView::~PlayerView() {
		// TODO Auto-generated destructor stub
	}

	void PlayerView::render(shared_ptr<Scene> gameScene)
	{

		renderer->clearScreen();

		if(gameScene->showingStartScreen) {
			float startScreenVerts[16] =
			{
				1.0f, 1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f, 1.0f,
				-1.0f, -1.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 1.0f, 1.0f
			};

			renderer->renderTexturedQuad(&startScreenVerts[0], "startScreen");

			/*SDL_Color textColour = {255, 255, 0, 255};
			renderer->renderText("Now it's chasing me! HELP!", textColour, -1.0f, 1.0f, 1.0f, 0.5f);*/
		}
		else
		{
			// Draw the background

			float groundVerts[16] =
			{
				1.0f, 0.0f, 1.0f, 1.0f,
				-1.0f, 0.0f, 1.0f, 1.0f,
				-1.0f, -1.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 1.0f, 1.0f
			};

			float skyVerts[16] =
			{
				1.0f, 1.0f, 1.0f, 1.0f,
				-1.0f, 1.0f, 1.0f, 1.0f,
				-1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, 0.0f, 1.0f, 1.0f
			};

			renderer->renderTexturedQuad(&groundVerts[0], "ground");
			renderer->renderTexturedQuad(&skyVerts[0], "sky");

			renderer->renderSceneObjects(gameScene->sceneObjects);

		}
		
		
		renderer->swapBuffers();
	}

} /* namespace AvoidTheBug3D */
