#pragma once

#include <SDL.h>

class GameObject
{
public:
	GameObject(int x, int y) : m_x(x), m_y(y) {}
	virtual void draw(SDL_Renderer* renderer) = 0;
	virtual void update(int ds) = 0;
	virtual void clean() = 0;

protected:
	int m_x;
	int m_y;

};

