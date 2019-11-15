#pragma once

#include <SDL.h>
#include <iostream>
#include "Tilemap.h"
#include "Player.h"
#include "BulletManager.h"

using namespace std;

class Bullet;

class Player;

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
	BulletManager * bm;
	SDL_Window* window;
	SDL_Renderer * renderer;

	Player * player;
	Tilemap * tilemap;
	bool keydown[256];

};


