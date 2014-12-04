#include <iostream>


#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
	Uint32 frameStart;
	Uint32 frameTime;

	Game::getInstance()->init("MyTetris", 100, 100, 500, 500);


	Uint32 lastFrame = SDL_GetTicks();
	while (Game::getInstance()->running())
	{
		frameStart = SDL_GetTicks();
		Uint32 elapsed = frameStart - lastFrame;
		Game::getInstance()->handleEvents();
		Game::getInstance()->update(0);
		Game::getInstance()->render();
		lastFrame = frameStart;

		frameTime = SDL_GetTicks() - frameStart;
		if (frameTime < DELAY_TIME)
		{
			SDL_Delay((int)DELAY_TIME - frameTime);
		}

	}


	Game::getInstance()->clean();

	return 0;
}