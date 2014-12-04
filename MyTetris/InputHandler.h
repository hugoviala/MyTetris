#pragma once

#include <SDL.h>
#include <vector>
#include <iostream>

#include "Game.h"
#include "Vector2D.h"

class InputHandler
{
public:
	static InputHandler* getInstance();

	void update();
	void clean();

	/*!
	 * \brief Methods for handling joysticks
	 */

	void initializeJoysticks();
	bool joysticksInitialized() { return m_joysticksInitialized; }
	int xvalue(int joy, int stick);
	int yvalue(int joy, int stick);
	bool getButtonState(int joy, int buttonNumber);

	/*!
	* \brief Methods for handling keyboard input
	*/
	//bool isKeyDown(SDL_Scancode key);


private:
	static InputHandler* s_instance;

	InputHandler();
	~InputHandler();

	/*!
	* \brief Variables for handling joystick motion
	*/
	bool m_joysticksInitialized;
	std::vector<SDL_Joystick*> m_joysticks;
	std::vector<std::pair<Vector2D*, Vector2D*> > m_joystickValues;
	const int m_joystickDeadZone = 10000;

	/*!
	 * \brief Variables for handling joystick button input
	*/
	std::vector<std::vector<bool> > m_buttonStates;

	/*!
	* \brief Variables for handling keyboard input
	*/
	//const Uint8* m_keystate;
};

