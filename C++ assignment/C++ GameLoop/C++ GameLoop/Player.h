#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Tilemap.h"

class Tilemap;

class Player {
public:
	Player(SDL_Renderer*, Tilemap*);

	bool DestroyEnemy = false;
	void init();
	void processInput(SDL_Event e);
	void update();
	void draw();
	void clean();

	float getxpos()
	{
		return xpos;
	}
	float getypos()
	{
		return ypos;
	}
	float getAngle()
	{
		return angle;
	}

	int playerwidth = 32;
	int playerheight = 32;
	int obstacles[25][25];

protected:

	float angle = 0;
	float xpos = 768;
	float ypos = 384;
	SDL_Rect position;
	SDL_Texture *playertexture;
	SDL_Texture *enemytexture;
	SDL_Renderer *renderer;
	Tilemap * tilemap;
};
