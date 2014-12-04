#pragma once

#include <string>
#include "GameObject.h"
#include "TileColor.h"
#include "TextureManager.h"

#define SIZE_X 10
#define SIZE_Y 20

class TileMap :
	public GameObject
{
public:
	static TileMap* getInstance()
	{
		if (s_instance == 0)
		{
			s_instance = new TileMap();
		}
		return s_instance;
	}
	virtual void draw(SDL_Renderer* renderer);
	virtual void update(int ds);
	virtual void clean();

	void addTiles(std::pair<int, int>* tiles, TileColor color);
	int addPoints();

	TileColor** getTileMap() const { return m_tilemap; }

private:
	static TileMap* s_instance;
	TileMap();
	~TileMap();
	TileColor** m_tilemap;
	int m_pointsToAdd;

	bool isRawFull(int j);
	void flood(int bottomLimit);
};

