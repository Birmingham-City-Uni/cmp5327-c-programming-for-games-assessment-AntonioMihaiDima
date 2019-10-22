#pragma once

#include <SDL.h>
#include <iostream>
#include "Tilemap.h"

using namespace std;



class GameLoop {

public:
	GameLoop();

	bool init();

	bool processInput();

	void update(); //returns true only if appplication is closed

	void draw();

	void clean();


private:
	SDL_Window* window;
	SDL_Renderer * renderer;

	Tilemap * tilemap;

};


