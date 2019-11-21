#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Tilemap.h"
#include <iostream>

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

	/*int getXSlot()
	{
		return xslot;
	}
	int getYSlot()
	{
		return yslot;
	}
	*/

	int playerwidth = 32;
	int playerheight = 32;
	int obstacles[26][26];

protected:

	int xslot;
	int yslot;
	float angle = 0;
	int xpos = 768;
	int ypos = 384;
	SDL_Rect position;
	SDL_Texture *playertexture;
	SDL_Texture *enemytexture;
	SDL_Renderer *renderer;
	Tilemap * tilemap;
};
