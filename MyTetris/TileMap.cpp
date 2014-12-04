#include "TileMap.h"

TileMap* TileMap::s_instance = 0;

TileMap::TileMap() : GameObject(50, 50), m_pointsToAdd(0)
{
	m_tilemap = new TileColor*[SIZE_X];
	for (int i = 0; i < SIZE_X; i++)
	{
		m_tilemap[i] = new TileColor[SIZE_Y];
		for (int j = 0; j < SIZE_Y; j++)
		{
			m_tilemap[i][j] = NONE;
		}
	}
}


TileMap::~TileMap()
{
}

void TileMap::draw(SDL_Renderer* renderer)
{
	for (int i = 0; i < SIZE_X; i++)
	{
		for (int j = 0; j < SIZE_Y; j++)
		{
			if (m_tilemap[i][j] != NONE)
			{
				std::string color;
				if (m_tilemap[i][j] == BLUE)
				{
					color = "blue";
				}
				else if (m_tilemap[i][j] == RED)
				{
					color = "red";
				}
				else if (m_tilemap[i][j] == GREEN)
				{
					color = "green";
				}
				else if (m_tilemap[i][j] == YELLOW)
				{
					color = "yellow";
				}
				else if (m_tilemap[i][j] == WHITE)
				{
					color = "white";
				}
				else if (m_tilemap[i][j] == PINK)
				{
					color = "pink";
				}
				else // if (m_tilemap[i][j] == BROWN)
				{
					color = "brown";
				}
				TextureManager::getInstance()->draw(color + "_tile", 50 + 20 * i, 50 + 20 * j, 20, 20, renderer);
			}
		}
	}
}

void TileMap::update(int ds)
{
	for (int j = SIZE_Y - 1; j >= 0; j--)
	{
		if (isRawFull(j))
		{
			m_pointsToAdd++;
			flood(j);
		}
	}
}

void TileMap::clean()
{
	for (int i = 0; i < SIZE_X; i++)
	{
		delete m_tilemap[i];
	}
	delete m_tilemap;
}

void TileMap::addTiles(std::pair<int, int>* tiles, TileColor color)
{
	for (int i = 0; i < 4; i++)
	{
		m_tilemap[tiles[i].first][tiles[i].second] = color;
	}
}

bool TileMap::isRawFull(int j)
{
	for (int i = 0; i < SIZE_X; i++)
	{
		if (m_tilemap[i][j] == NONE)
		{
			return false;
		}
	}

	return true;
}


void TileMap::flood(int bottomLimit)
{
	for (int j = bottomLimit - 1; j >= 0; j--)
	{
		for (int i = 0; i < SIZE_X; i++)
		{
			m_tilemap[i][j + 1] = m_tilemap[i][j];
		}
	}
	for (int i = 0; i < SIZE_X; i++)
	{
		m_tilemap[i][0] = NONE;
	}
}

int TileMap::addPoints()
{
	int temp = m_pointsToAdd;
	m_pointsToAdd = 0;
	return temp;
}
