#pragma once

#include <SDL.h>
#include <iostream>
#include "Tilemap.h"
#include "Player.h"
#include "BulletManager.h"
#include "EnemyManager.h"
#include "TextRenderer.h"
#include "Sound.h"

using namespace std;

class BulletManager;

class Player;

class Tilemap;

class EnemyManager;

class TextRenderer;

class AudioManager;

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
	EnemyManager * em;
	SDL_Window* window;
	SDL_Renderer * renderer;
	AudioManager * sound;
	Player * player;
	Tilemap * tilemap;
	TextRenderer* textRenderer;
	bool keydown[256];

};


