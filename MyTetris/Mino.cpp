#include "Mino.h"


Mino::Mino(int x, int y, bool updatable, MinoType t) : GameObject(x, y), m_updatable(updatable), m_rotNumber(0), m_collided(false), m_type(t)
{
	m_tiles = initPositions(t);
	m_lastTimeUpdated = SDL_GetTicks();
	m_lastTimeWentDown = SDL_GetTicks();
	m_color = colorFromType(t);
}


Mino::~Mino()
{
	delete m_tiles;
}

void Mino::update(int ds)
{
	if (m_updatable)
	{
		int currentTime = SDL_GetTicks();
		if (currentTime - m_lastTimeUpdated > 80)
		{
				if (InputHandler::getInstance()->getButtonState(0, 10))
				{
					std::pair<int, int>* newTiles = rotation(m_tiles);
					if (!collision(newTiles))
					{
						delete m_tiles;
						m_tiles = newTiles;
						m_rotNumber = (m_rotNumber + 1) % 4;
					}
					else
					{
						delete newTiles;
					}
				}
				else if (InputHandler::getInstance()->xvalue(0, 1) > 0)
				{
					std::pair<int,int>* newTiles = positionsFromAnchor(m_type, m_tiles[0].first + 1, m_tiles[0].second);
					for (int i = 0; i < m_rotNumber; i++)
					{
						newTiles = rotation(newTiles);
					}
					if (!collision(newTiles))
					{
						delete m_tiles;
						m_tiles = newTiles;
					}
					else
					{
						delete newTiles;
					}
				}
				else if (InputHandler::getInstance()->xvalue(0, 1) < 0)
				{
					std::pair<int, int>* newTiles = positionsFromAnchor(m_type, m_tiles[0].first - 1, m_tiles[0].second);
					for (int i = 0; i < m_rotNumber; i++)
					{
						newTiles = rotation(newTiles);
					}
					if (!collision(newTiles))
					{
						delete m_tiles;
						m_tiles = newTiles;
					}
					else
					{
						delete newTiles;
					}
				}
			m_lastTimeUpdated = SDL_GetTicks();
		}
		if (currentTime - m_lastTimeWentDown > downSpeed())
		{
			std::pair<int, int>* newTiles = positionsFromAnchor(m_type, m_tiles[0].first, m_tiles[0].second + 1);
			for (int i = 0; i < m_rotNumber; i++)
			{
				newTiles = rotation(newTiles);
			}
			if (!collision(newTiles, true))
			{
				delete m_tiles;
				m_tiles = newTiles;
			}
			else
			{
				delete newTiles;
			}
			m_lastTimeWentDown = SDL_GetTicks();
		}
	}
}

void Mino::draw(SDL_Renderer* renderer)
{
	if (m_updatable)
	{
		for (int i = 0; i < 4; i++)
		{
			TextureManager::getInstance()->draw(stringFromColor() + "_tile", 50 + 20 * m_tiles[i].first, 50 + 20 * m_tiles[i].second, 20, 20, renderer);
		}
	}
	else
	{
		for (int i = 0; i < 4; i++)
		{
			TextureManager::getInstance()->draw(stringFromColor() + "_tile", 270 + 20 * m_tiles[i].first, 120 + 20 * m_tiles[i].second, 20, 20, renderer);
		}
	}
}

void Mino::clean()
{
	delete m_tiles;
}

std::pair<int, int>* Mino::rotation(std::pair<int, int>* tiles) const
{
	std::pair<int, int>* m_newTiles = new std::pair<int, int>[4];
	m_newTiles[0] = tiles[0]; // The anchor tile does not move.

	const int i = tiles[0].first;
	const int j = tiles[0].second;

	for (int k = 1; k < 4; k++)
	{
		m_newTiles[k] = std::make_pair(tiles[k].second - j + i, - tiles[k].first + i + j);
	}

	return m_newTiles;
}

std::pair<int, int>* Mino::initPositions(MinoType t)
{
	return positionsFromAnchor(t, 4, 1);
}

std::pair<int, int>* Mino::positionsFromAnchor(MinoType t, int i_anchor, int j_anchor)
{
	std::pair<int, int>* m_newTiles = new std::pair<int, int>[4];

	m_newTiles[0] = std::make_pair(i_anchor, j_anchor);
	if (t == I)
	{
		m_newTiles[1] = std::make_pair(i_anchor - 1, j_anchor);
		m_newTiles[2] = std::make_pair(i_anchor + 1, j_anchor);
		m_newTiles[3] = std::make_pair(i_anchor + 2, j_anchor);
	}
	else if (t == J)
	{
		m_newTiles[1] = std::make_pair(i_anchor, j_anchor - 1);
		m_newTiles[2] = std::make_pair(i_anchor + 1, j_anchor);
		m_newTiles[3] = std::make_pair(i_anchor + 2, j_anchor);
	}
	else if (t == L)
	{
		m_newTiles[1] = std::make_pair(i_anchor - 2, j_anchor );
		m_newTiles[2] = std::make_pair(i_anchor - 1, j_anchor);
		m_newTiles[3] = std::make_pair(i_anchor, j_anchor - 1);
	}
	else if (t == O)
	{
		m_newTiles[1] = std::make_pair(i_anchor, j_anchor + 1);
		m_newTiles[2] = std::make_pair(i_anchor + 1, j_anchor);
		m_newTiles[3] = std::make_pair(i_anchor + 1, j_anchor + 1);
	}
	else if (t == S)
	{
		m_newTiles[1] = std::make_pair(i_anchor - 1, j_anchor);
		m_newTiles[2] = std::make_pair(i_anchor, j_anchor - 1);
		m_newTiles[3] = std::make_pair(i_anchor + 1, j_anchor - 1);
	}
	else if(t == T)
	{
		m_newTiles[1] = std::make_pair(i_anchor - 1, j_anchor);
		m_newTiles[2] = std::make_pair(i_anchor + 1, j_anchor);
		m_newTiles[3] = std::make_pair(i_anchor, j_anchor - 1);
	}
	else // if(t == Z)
	{
		m_newTiles[1] = std::make_pair(i_anchor - 1, j_anchor);
		m_newTiles[2] = std::make_pair(i_anchor, j_anchor + 1);
		m_newTiles[3] = std::make_pair(i_anchor + 1, j_anchor + 1);
	}

	return m_newTiles;
}

bool Mino::collision(std::pair<int, int>* tiles, bool goingDown)
{
	for (int k = 0; k < 4; k++)
	{
		const int i = tiles[k].first;
		const int j = tiles[k].second;

		if (i < 0 || i >= 10 || j < 0 || j >= 20 || TileMap::getInstance()->getTileMap()[i][j] != NONE)
		{
			if (goingDown)
			{
				TileMap::getInstance()->addTiles(m_tiles, m_color);
				m_collided = true;
			}
			return true;
		}
	}
	return false;
}

int Mino::downSpeed() const
{
	if (InputHandler::getInstance()->yvalue(0, 1) > 0)
	{
		return 50;
	}
	else
	{
		return 700;
	}
}


TileColor Mino::colorFromType(MinoType t)
{
	if (t == I)
	{
		return WHITE;
	}
	else if (t == J)
	{
		return RED;
	}
	else if (t == L)
	{
		return BLUE;
	}
	else if (t == O)
	{
		return YELLOW;
	}
	else if (t == S)
	{
		return GREEN;
	}
	else if (t == T)
	{
		return PINK;
	}
	else // if(t == Z)
	{
		return BROWN;
	}
}
std::string Mino::stringFromColor()
{
	if (m_color == BLUE)
	{
		return "blue";
	}
	else if (m_color == RED)
	{
		return "red";
	}
	else if (m_color == GREEN)
	{
		return "green";
	}
	else if (m_color == YELLOW)
	{
		return "yellow";
	}
	else if (m_color == WHITE)
	{
		return "white";
	}
	else if (m_color == PINK)
	{
		return "pink";
	}
	else // if (m_color == BROWN)
	{
		return "brown";
	}
}

