#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <cstdlib>
#include <iostream>
#include <dimitrikourk/small3d/EngineLog.h>
#include <dimitrikourk/small3d/EngineException.h>
#include <memory>
#include "GameLogic.h"
#include "PlayerView.h"
#include "KeyInput.h"

using namespace std;
using namespace AvoidTheBug3D;
using namespace small3d;

const GLuint frameRate = 60;

int main(int argc, char** argv)
{

	KeyInput input;

	shared_ptr<EngineLog> log(new EngineLog(cout));

	shared_ptr<Configuration> cfg(new Configuration(log));

	try
	{

		shared_ptr<GameLogic> gameLogic(new GameLogic(cfg, log));

		shared_ptr<PlayerView> pv(new PlayerView(cfg, log));

		// program main loop
		bool done = false;

		// ticks for setting the frame rate
		GLuint ticks = SDL_GetTicks();
		GLuint prevTicks = ticks;
		GLuint ticksInterval = 1000 / frameRate;

		while (!done)
		{

			SDL_Event event;
			if (SDL_PollEvent(&event))
			{

				const Uint8 *keyState = SDL_GetKeyboardState(NULL);

				input.up = keyState[SDL_SCANCODE_UP] == 1;
				input.down = keyState[SDL_SCANCODE_DOWN] == 1;
				input.left = keyState[SDL_SCANCODE_LEFT] == 1;
				input.right = keyState[SDL_SCANCODE_RIGHT] == 1;
				input.enter = keyState[SDL_SCANCODE_RETURN] == 1;

				switch (event.type)
				{

				case SDL_QUIT:
					done = true;
					break;

				case SDL_KEYDOWN:
					{
						if (event.key.keysym.sym == SDLK_ESCAPE)
							done = true;
						break;
					}
				}
			}

			ticks = SDL_GetTicks();
			if (ticks - prevTicks > ticksInterval)
			{
				gameLogic->process(input);
				prevTicks = ticks;
				pv->render(gameLogic->gameScene);
			}
		}

	}
	catch (EngineException &e)
	{
		LOGERROR(e.what());
		return 1;
	}

	return 0;
}
