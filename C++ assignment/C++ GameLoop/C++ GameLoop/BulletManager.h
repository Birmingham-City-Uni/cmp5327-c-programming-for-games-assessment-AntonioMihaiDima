#pragma once

//SDL header files
#include <SDL.h>
#include <SDL_image.h>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "Tilemap.h"





#define PI 3.14159265

class Player;
class Tilemap;
using namespace std;


class BulletManager {
	friend class EnemyManager;
public:
	BulletManager(SDL_Renderer * renderer, Player * player, Tilemap * tilemaparraypointer) : renderer(renderer), player(player), tilemaparraypointer(tilemaparraypointer) {}


	void init() {
		//load the texture for the bullet
		SDL_Surface * surface = IMG_Load("debug/BulletTexture.png");
		this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
	}

	void processInput(bool * keydown) {
		if (player->EndGame == false)
		{
			if ((player->NoMoreEnemies == false) && (player->Reloading == false))
				if (keydown[SDL_SCANCODE_SPACE]) {
					if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS) {
						if (int(player->getAngle()) == 0)
						{
							x = player->getypos() + 18;
							y = player->getxpos();
							rotation = player->getAngle();
							distance = 0;
						}
						if (int(player->getAngle()) == 270)
						{
							x = player->getypos();
							y = player->getxpos() + 5;
							rotation = player->getAngle();
							distance = 0;
						}
						if (int(player->getAngle()) == 180)
						{
							x = player->getypos() + 5;
							y = player->getxpos() + 20;
							rotation = player->getAngle();
							distance = 0;
						}
						if (int(player->getAngle()) == 90)
						{
							x = player->getypos() + 20;
							y = player->getxpos() + 16;
							rotation = player->getAngle();
							distance = 0;
						}
						IsShooting = true;
						lastShot = SDL_GetTicks();
						player->BulletNumber -= 1;
					}
				}
		}
	}

	void update() {
		
	
			if (IsShooting) {
				x += sin(rotation * PI / 180.0f)* BULLET_VELOCITY;
				y -= cos(rotation * PI / 180.0f)* BULLET_VELOCITY;
				distance += BULLET_VELOCITY;
			}

			if (distance > 1501)
				IsShooting = false;
		
	}

	void draw() {
		
		if (IsShooting) {
			SDL_Point center = { 5, 5 };
			SDL_Rect dest = { x, y, 11, 11 };



			for (int i = 0; i < 24; i++)
				for (int j = 0; j < 24; j++)
					if ((player->obstacles[int(y / 32)][int(x / 32)] == 1) || (player->obstacles[int(y / 32)][int(x / 32)] == 4))
						distance = 1501;


			SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, rotation, &center, SDL_FLIP_NONE);
		}
	}

	void clean() {
		SDL_DestroyTexture(this->bulletTexture);
	}

	Player * player;

private:
	SDL_Renderer * renderer;
	SDL_Texture * bulletTexture;
	
	Tilemap *tilemaparraypointer;

	//time limit between shots
	const int SHOOT_TIMER_MS = 2300;
	//numer of pixels travelled per frame
	const int BULLET_VELOCITY = 10;
	unsigned int lastShot = 0;
	float x;
	float y;
	float rotation;
	float distance = 0;
	bool IsShooting = false;

};