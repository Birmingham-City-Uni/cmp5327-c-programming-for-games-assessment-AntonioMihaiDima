#pragma once

#include <SDL.h>
#include <iostream>
#include "Tilemap.h"

using namespace std;

class Tilemap;

class GameLoop {

public:
	GameLoop();

	bool init();

	bool processInput();

	void update(); //returns true only if appplication is closed

	void draw();

	void clean();

	bool getKeyDown(int keyCode)
	{
		if (keyCode > 0 && keyCode < 512)
		{
			return this->keydown[keyCode];
		}
		return false;
	}


private:
	SDL_Window* window;
	SDL_Renderer * renderer;

	Tilemap * tilemap;
	bool keydown[256];

};


