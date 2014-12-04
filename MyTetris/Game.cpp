#include "Game.h"


Game* Game::s_instance = 0;

void Game::init(char* title, int x, int y, int width, int height, Uint32 flags)
{
	m_state = TITLE_STATE;
	m_score = 0;
	m_wantOutOfPause = false;
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		m_window = SDL_CreateWindow(title, x, y, width, height, flags);
		m_renderer = SDL_CreateRenderer(m_window, -1, 0);
		SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
		m_running = true;
	}

	initGameObjects();
	initTextures();

}

Game::Game()
{
	srand(time(NULL));
	m_currentMino = new Mino(0, 0, true, getRandomType());
	m_nextMino = new Mino(0, 0, false, getRandomType());
}


Game::~Game()
{
	delete m_currentMino;
	delete m_nextMino;
}

void Game::update(int ds)
{
	const int pause_button = 4;
	if (m_state == TITLE_STATE && InputHandler::getInstance()->getButtonState(0, 10))
	{
		m_state = INGAME_STATE;
	}
	if (m_state == INGAME_STATE && InputHandler::getInstance()->getButtonState(0, pause_button))
	{
		m_state = PAUSE_STATE;
	}
	else if (m_state == PAUSE_STATE && !m_wantOutOfPause && !InputHandler::getInstance()->getButtonState(0, pause_button))
	{
		m_state = TRUE_PAUSE_STATE;
	}
	else if (m_state == TRUE_PAUSE_STATE && InputHandler::getInstance()->getButtonState(0, pause_button))
	{
		m_state = PAUSE_STATE;
		m_wantOutOfPause = true;
	}
	else if (m_state == PAUSE_STATE && m_wantOutOfPause && !InputHandler::getInstance()->getButtonState(0, pause_button))
	{
		m_state = INGAME_STATE;
		m_wantOutOfPause = false;
	}
	else if (m_state == GAME_OVER_STATE && InputHandler::getInstance()->getButtonState(0, 10))
	{
		quit();
	}

	if (m_state == INGAME_STATE)
	{
		TileMap::getInstance()->update(0);
		m_score += TileMap::getInstance()->addPoints();
		m_currentMino->update(0);
		m_nextMino->update(0);
		if (m_currentMino->collided())
		{
			updateMinos();
		}

	}
}

void Game::handleEvents()
{
	InputHandler::getInstance()->update();
}

void Game::render()
{
	SDL_RenderClear(m_renderer);
	if (m_state == TITLE_STATE)
	{
		TextureManager::getInstance()->draw("title_screen", 0, 0, 500, 500, m_renderer);
	}
	else
	{
		if (m_state == INGAME_STATE || m_state == PAUSE_STATE || m_state == TRUE_PAUSE_STATE || m_state == GAME_OVER_STATE)
		{
			TextureManager::getInstance()->draw("screen", 0, 0, 500, 500, m_renderer);
			TileMap::getInstance()->draw(m_renderer);
			m_currentMino->draw(m_renderer);
			m_nextMino->draw(m_renderer);
			char* text = textFromScore();
			SDL_Color color = { 255, 255, 255 };
			TextureManager::getInstance()->write(text, 305, 300, 140, 100, m_renderer, color);
			delete text;
		}
		if (m_state == TRUE_PAUSE_STATE)
		{
			TextureManager::getInstance()->draw("pause_screen", 0, 0, 500, 500, m_renderer);
		}
		if (m_state == GAME_OVER_STATE)
		{
			TextureManager::getInstance()->draw("game_over_screen", 0, 0, 500, 500, m_renderer);
			char* text = textFromScore();
			SDL_Color color = { 0, 0, 0 };
			TextureManager::getInstance()->write(text, 175, 350, 140, 100, m_renderer, color);
			delete text;
		}
	}

	SDL_RenderPresent(m_renderer);
}

void Game::clean()
{
	TileMap::getInstance()->clean();
	m_currentMino->clean();
	m_nextMino->clean();

	SDL_DestroyWindow(m_window);
	SDL_DestroyRenderer(m_renderer);
	SDL_Quit();
}

void Game::initTextures()
{
	TextureManager::getInstance()->load("screen.png", "screen", m_renderer);
	TextureManager::getInstance()->load("white_tile.png", "white_tile", m_renderer);
	TextureManager::getInstance()->load("blue_tile.png", "blue_tile", m_renderer);
	TextureManager::getInstance()->load("brown_tile.png", "brown_tile", m_renderer);
	TextureManager::getInstance()->load("green_tile.png", "green_tile", m_renderer);
	TextureManager::getInstance()->load("pink_tile.png", "pink_tile", m_renderer);
	TextureManager::getInstance()->load("yellow_tile.png", "yellow_tile", m_renderer);
	TextureManager::getInstance()->load("red_tile.png", "red_tile", m_renderer);

	TextureManager::getInstance()->load("pause_screen.png", "pause_screen", m_renderer);
	TextureManager::getInstance()->load("title_screen.png", "title_screen", m_renderer);
	TextureManager::getInstance()->load("game_over_screen.png", "game_over_screen", m_renderer);
}


void Game::initGameObjects()
{

}

MinoType Game::getRandomType()
{
	int randomNumber = rand() % 7;
	switch (randomNumber)
	{
	case 0:
		return I;
		break;
	case 1:
		return J;
		break;
	case 2:
		return L;
		break;
	case 3:
		return O;
		break;
	case 4:
		return S;
		break;
	case 5:
		return T;
		break;
	case 6:
		return Z;
		break;
	}
}

void Game::updateMinos()
{
	//m_currentMino->clean();
	delete m_currentMino; // peut être remplacer m_current mino et m_nextMino par directement leur position dans gameobjects
	m_currentMino = new Mino(0, 0, true, m_nextMino->getType());
	//m_nextMino->clean();
	delete m_nextMino;
	if (m_currentMino->collision(m_currentMino->getTiles()))
	{
		gameOver();
	}
	m_nextMino = new Mino(0, 0, false, getRandomType());
}

void Game::gameOver()
{
	m_state = GAME_OVER_STATE;
}

char* Game::textFromScore()
{
	char* text = new char[4];
	int a = m_score / 1000;
	int b = (m_score / 100) - 10 * a;
	int c = (m_score / 10) - 100 * a - 10 * b;
	int d = m_score - 1000 * a - 100 * b - 10 * c;
	text[0] = (char)(((int)'0') + a);
	text[1] = (char)(((int)'0') + b);
	text[2] = (char)(((int)'0') + c);
	text[3] = (char)(((int)'0') + d);

	return text;
}
