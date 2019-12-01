#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include "BulletManager.h"
#include "Time.h"


#define PI 3.14159265

class BulletManager;
using namespace std;



struct Enemy {

	float x, y, rotation, distance;
	int randommove;
	int directionpicked = 0;
	bool bottomcollision = false;
	bool directiontobepicked = false;

};


class EnemyManager {

public:
	EnemyManager(SDL_Renderer * renderer, BulletManager* bulletmanager) : renderer(renderer), bulletmanager(bulletmanager) {}

	int enemiesremaining = 6;
	bool Scoregained = false;

	void init()
	{
		SDL_Surface * Enemy1Surface = IMG_Load("debug/Enemy1.png");
		Enemy1 = SDL_CreateTextureFromSurface(this->renderer, Enemy1Surface);
		SDL_FreeSurface(Enemy1Surface);

		/*SDL_Surface * Enemy2Surface = IMG_Load("debug/Enemy2.png");
		Enemy2 = SDL_CreateTextureFromSurface(this->renderer, Enemy2Surface);
		SDL_FreeSurface(Enemy2Surface);

		SDL_Surface * Enemy3Surface = IMG_Load("debug/Enemy3.png");
		Enemy3 = SDL_CreateTextureFromSurface(this->renderer, Enemy3Surface);
		SDL_FreeSurface(Enemy3Surface);

		SDL_Surface * Enemy4Surface = IMG_Load("debug/Enemy4.png");
		Enemy4 = SDL_CreateTextureFromSurface(this->renderer, Enemy4Surface);
		SDL_FreeSurface(Enemy4Surface);
		*/

		srand(time(0));



	}


	void update()
	{
		if (enemycount < MaxEnemies)
			if (SDL_GetTicks() - lastSpawn > SpawnMs && distancetravelled == 0)
			{
				spawnpicker = rand() % 23 + 1;
				enemies.push_back(Enemy{ 0, float(spawnpicker * 32) , angle, 0.0f });
				//typeofenemy.push_back(rand() % 4);
				enemycount++;
				lastSpawn = SDL_GetTicks();
				cout << SDL_GetTicks() << " ";
			}





		if (distancetravelled < 32)
		{
			for (auto &e : enemies)
			{



				if (e.directiontobepicked == false)
				{
					if ((bulletmanager->player->obstacles[int(e.x / 32) + 1][int(e.y / 32)] == 0) && (e.bottomcollision == false))
					{

						e.directionpicked = 0;
						e.rotation = 0;

					}
					else if (bulletmanager->player->obstacles[int(e.x / 32)][int(e.y / 32) + 1] == 0)
					{
						//e.x -= 32;
						e.directionpicked = 1;
						e.bottomcollision = false;
						e.rotation = 270;

					}
					else if (bulletmanager->player->obstacles[int(e.x / 32)][int(e.y / 32) - 1] == 0)
					{
						//e.x -= 32;
						e.directionpicked = 2;
						e.bottomcollision = false;
						e.rotation = 90;
					}
					else
					{
						//e.x -= 32;
						e.directionpicked = 3;
						e.bottomcollision = true;
						e.rotation = 180;
					}

					e.directiontobepicked = true;
				}


				if (e.directionpicked == 0)
				{
					e.x += 2;
				}
				if (e.directionpicked == 1)
				{
					e.y += 2;
				}
				if (e.directionpicked == 2)
				{
					e.y -= 2;
				}
				if (e.directionpicked == 3)
				{
					e.x -= 2;
				}



			}

			distancetravelled += 2;

			if (distancetravelled == 32)
			{
				for (auto &e : enemies)
				{
					e.directiontobepicked = false;
				}
				distancetravelled = 0;
			}

		}

		for (auto &e : enemies)
		{
			if (e.x > 768)
			{
				enemiesremaining--;
				cout << enemiesremaining << " ";
			}
		}


		auto remove = std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return e.x > 768; });
		
			enemies.erase(remove, enemies.end());

			if(bulletmanager->tilemaparraypointer->mapscrolled)
			{
				MaxEnemies += 2;
				enemiesremaining = MaxEnemies;
				enemycount = 0;
				bulletmanager->tilemaparraypointer->WaveComplete = false;
				bulletmanager->player->perfectxpos = false;
				bulletmanager->tilemaparraypointer->mapscrolled = false;
				bulletmanager->player->distancetravelled = 0;
			}


			//Here we just check if any enemies are alive so we can stop the player movement.
			if (enemiesremaining <= 0)
			{
				bulletmanager->player->NoMoreEnemies = true;
			}
			
			else if (enemiesremaining > 0)
			{
				bulletmanager->player->NoMoreEnemies = false;
			}

			for (auto &e : enemies) {
				for (auto &b : bulletmanager->bullets)
				{
					SDL_Rect dest = { e.y, e.x, 32, 32 };
					SDL_Rect bulletrect = { b.x, b.y, 11, 11 };
					SDL_Rect nullRect;
					if (SDL_IntersectRect(&bulletrect, &dest, &nullRect))
					{
						Scoregained = true;
						e.x = 800;
						b.distance = 1501;

					}
				}
			}
			

	}


	void draw()
	{
		for (auto &e : enemies)
		{
			SDL_Point center = { 5, 5 };

			SDL_Rect dest = { e.y, e.x, 32, 32 };

			SDL_RenderCopyEx(renderer, Enemy1, 0, &dest, e.rotation, &center, SDL_FLIP_NONE);



		}

	}

private:
	SDL_Renderer * renderer;
	vector<Enemy> enemies;
	BulletManager * bulletmanager;
	SDL_Texture * Enemy1;
	SDL_Texture * Enemy2;
	SDL_Texture * Enemy3;
	SDL_Texture * Enemy4;
	SDL_Surface * Enemy1Surface;
	SDL_Surface * Enemy2Surface;
	SDL_Surface * Enemy3Surface;
	SDL_Surface * Enemy4Surface;

	const int SpawnMs = 4000;
	unsigned int lastSpawn = 0;
	int MaxEnemies = 6;
	int spawnpicker;
	float angle = 0;
	int enemypicker;
	int enemycount = 0;
	int distancetravelled = 0;
	int enemytype = 0;
	int enemynumber = 0;







};
