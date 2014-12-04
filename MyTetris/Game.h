#pragma once

#include <SDL.h>
#include <vector>

#include <time.h>
#include <stdlib.h>

#include "InputHandler.h"
#include "TextureManager.h"

#include "GameObject.h"


#include "TileMap.h"
#include "Mino.h"
#include "MinoType.h"

#include "GameState.h"

class Mino;
class Game
{
public:
	static Game* getInstance()
	{
		if (s_instance == 0)
		{
			s_instance = new Game();
		}
		return s_instance;
	}


	void init(char* title, int x, int y, int width, int height, Uint32 flags = 0);

	void update(int ds);
	void render();
	void clean();
	void handleEvents();

	bool running() const { return m_running; }

	void quit() { m_running = false; }

	void gameOver();

	int getScore() const { return m_score; }

private:
	static Game* s_instance;

	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool m_running;

	std::vector<GameObject*> m_gameObjects;
	Mino* m_currentMino;
	Mino* m_nextMino;
	GameState m_state;
	bool m_wantOutOfPause;

	int m_score;

	Game();
	~Game();
	void initTextures();
	void initGameObjects();
	
	MinoType getRandomType();
	void updateMinos();
	char* textFromScore();
};

