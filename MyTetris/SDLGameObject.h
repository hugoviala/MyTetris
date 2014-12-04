#pragma once

#include <string>

#include "GameObject.h"
#include "TextureManager.h"

class SDLGameObject : public GameObject
{
public:
	SDLGameObject(std::string textureID, int width, int height, int x, int y) :
		m_textureID(textureID),
		m_width(width),
		m_height(height),
		GameObject(x,y)
	{

	}

	virtual void draw(SDL_Renderer* renderer) { TextureManager::getInstance()->draw(m_textureID, m_x, m_y, m_width, m_height, renderer); }
	virtual void update(int ds) = 0;
	virtual void clean() = 0;



protected:
	std::string m_textureID;
	int m_width;
	int m_height;
};

