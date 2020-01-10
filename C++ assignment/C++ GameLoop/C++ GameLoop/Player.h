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
	bool EndGame = false;
	int BulletNumber = 7;
	bool Reloading = false;
	float ReloadTimer = 0;

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
	int obstacles[26][26];
	bool NoMoreEnemies = false;

	bool upmovement = false;
	bool downmovement = false;
	bool leftmovement = false;
	bool rightmovement = false;
	bool leftdirection = false;

	int distancetravelled = 0;
	bool directiontobepicked = false;
	int directionpicked;
	bool perfectxpos = false;


protected:

	int xslot;
	int yslot;
	float angle = 0;
	int xpos = 768;
	int ypos = 384;
	SDL_Rect position;
	SDL_Texture *playertexture;
	SDL_Texture * PlayerReload;
	SDL_Texture * Bullet;
	SDL_Texture * BulletAnimated;
	float BulletRotation = 270;
	SDL_Renderer *renderer;
	Tilemap * tilemap;

	int AnimationNumber = 1;
};
