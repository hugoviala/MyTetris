#pragma once

#include <utility>
#include <string>
#include "SDL.h"

#include "GameObject.h"
#include "MinoType.h"
#include "TextureManager.h"
#include "InputHandler.h"

class Mino :
	public GameObject
{
public:
	Mino(int x, int y, bool updatable, MinoType type);
	~Mino();
	virtual void draw(SDL_Renderer* renderer);
	virtual void update(int ds);
	virtual void clean();

	bool collided() const { return m_collided; }
	MinoType getType() const { return m_type; }

	std::pair<int, int>* getTiles() const { return m_tiles; }
	bool collision(std::pair<int, int>* tiles, bool goingDown = false);

private:
	/*!
	 * \fn rotation 
	 * \brief  A function proposing the array of the new tiles after a PI/2-rotation.
	 * \param tiles the array of the four tiles
	 * \returns the positions of the tiles after the rotation
	 * \remark it must be check if this array does not collide with something else
     */
	std::pair<int, int>* rotation(std::pair<int, int>* tiles) const;


	std::pair<int, int>* initPositions(MinoType t);


	std::pair<int, int>* positionsFromAnchor(MinoType t, int i_anchor, int j_anchor);



	int downSpeed() const; 

	TileColor colorFromType(MinoType t);
	std::string stringFromColor();



	/*!
	 * \brief m_tiles An array remember the position of the 4 tiles of the mino. m_tiles[0] is the anchor position
     */
	std::pair<int, int>* m_tiles;
	bool m_updatable;
	Uint32 m_lastTimeUpdated;
	Uint32 m_lastTimeWentDown;
	int m_rotNumber;
	bool m_collided;
	TileColor m_color;
	MinoType m_type;

};

