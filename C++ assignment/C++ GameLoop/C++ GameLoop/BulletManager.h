#pragma once

//SDL header files
#include <SDL.h>
#include <SDL_image.h>
//vector for the bullet array
#include <vector>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "Tilemap.h"


//int temparray[25][25];


#define PI 3.14159265

class Player;
class Tilemap;
using namespace std;


struct Bullet {
	float x, y, rotation, distance;
};

class BulletManager {
public:
	BulletManager(SDL_Renderer * renderer, Player * player, Tilemap * tilemaparraypointer) : renderer(renderer), player(player), tilemaparraypointer(tilemaparraypointer) {}


	void init() {
		//load the texture for the bullet
		SDL_Surface * surface = IMG_Load("debug/BulletTexture.png");
		this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
	}

	void processInput(bool * keydown) {
		if (keydown[SDL_SCANCODE_SPACE]) {
			if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS) {
				bullets.push_back(Bullet{ player->getypos() + 18, player->getxpos(), player->getAngle(), 0.0f });
				lastShot = SDL_GetTicks();
			}
		}
	}

	void update() {
		for (auto &b : bullets) {
			b.x += sin(b.rotation * PI / 180.0f)* BULLET_VELOCITY;
			b.y -= cos(b.rotation * PI / 180.0f)* BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
		//remove bullet after they have travelled approx 1500 pixels. this code could be called less frequently for efficiency
		auto remove = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) { return b.distance > 1500; });
		bullets.erase(remove, bullets.end());

		for (int i = 0; i < 24; i++)
			for (int j = 0; j <= 24; j++)
			{

			}

	}

	void draw() {
		SDL_Point center = { 5, 5 };
		for (auto &b : bullets) {
			SDL_Rect dest = { b.x, b.y, 11, 11 };

			for (int i = 0; i < 24; i++)
				for (int j = 0; j < 24; j++)
					if (tilemaparraypointer->tilemaparray[(int(b.y / 32))][(int(b.x / 32))] == 1)
						b.distance = 1501;




			SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
		}
	}

	void clean() {
		SDL_DestroyTexture(this->bulletTexture);
	}


private:
	SDL_Renderer * renderer;
	SDL_Texture * bulletTexture;
	vector<Bullet> bullets;
	//need a reference to the player to get the angle
	Player * player;
	Tilemap *tilemaparraypointer;

	//time limit between shots
	const int SHOOT_TIMER_MS = 2300;
	//numer of pixels travelled per frame
	const int BULLET_VELOCITY = 10;
	unsigned int lastShot = 0;

};