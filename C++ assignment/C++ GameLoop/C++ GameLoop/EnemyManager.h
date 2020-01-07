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
	friend class TextRenderer;

public:
	EnemyManager(SDL_Renderer * renderer, BulletManager* bulletmanager) : renderer(renderer), bulletmanager(bulletmanager) {}

	int enemiesremaining = 6;
	bool Scoregained = false;

	void init()
	{	Enemy1Surface = IMG_Load("debug/Enemy1.png");
		Enemy1 = SDL_CreateTextureFromSurface(this->renderer, Enemy1Surface);
		SDL_FreeSurface(Enemy1Surface);

		SDL_Surface * HealthSurface = IMG_Load("debug/health.png");
		HealthBar = SDL_CreateTextureFromSurface(this->renderer, HealthSurface);
		SDL_FreeSurface(HealthSurface);
		SDL_Surface * NoHealthSurface = IMG_Load("debug/nohealth.png");
		NoHealthBar = SDL_CreateTextureFromSurface(this->renderer, NoHealthSurface);
		SDL_FreeSurface(NoHealthSurface);


		srand(time(0));



	}


	void update()
	{
		if (bulletmanager->player->EndGame == false)
		{
			if (enemycount < MaxEnemies)
				if (SDL_GetTicks() - lastSpawn > SpawnMs && distancetravelled == 0)
				{
					spawnpicker = rand() % 23 + 1;
					enemies.push_back(Enemy{ 0, float(spawnpicker * 32) , angle, 0.0f });
					enemycount++;
					lastSpawn = SDL_GetTicks();
					//cout << SDL_GetTicks() << " ";
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
							e.directionpicked = 1;
							e.bottomcollision = false;
							e.rotation = 270;

						}
						else if (bulletmanager->player->obstacles[int(e.x / 32)][int(e.y / 32) - 1] == 0)
						{
							e.directionpicked = 2;
							e.bottomcollision = false;
							e.rotation = 90;
						}
						else
						{
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
					//cout << enemiesremaining << " ";
					if (!EnemyHit)
						healthsubstract += 80;
					else
					{
						EnemyHit = false;
					}
				}
			}

			if (healthsubstract == 800)
			{
				bulletmanager->player->EndGame = true;
			}


			auto remove = std::remove_if(enemies.begin(), enemies.end(), [](const Enemy& e) { return e.x > 768; });

			enemies.erase(remove, enemies.end());

			if (bulletmanager->tilemaparraypointer->mapscrolled)
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
						EnemyHit = true;
						Scoregained = true;
						e.x = 800;
						b.distance = 1501;

					}
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
		SDL_Rect NoHealthRect = { 0, 800, 800, 32 };
		SDL_RenderCopy(this->renderer, NoHealthBar, NULL, &NoHealthRect);
		SDL_Rect HealthRect = { 0, 800, 80 * 10 - healthsubstract, 32 };
		SDL_RenderCopy(this->renderer, HealthBar, NULL, &HealthRect);


	}

protected:
	SDL_Renderer * renderer;
	vector<Enemy> enemies;
	BulletManager * bulletmanager;
	SDL_Texture * Enemy1;
	SDL_Surface * Enemy1Surface;
	SDL_Texture * HealthBar;
	SDL_Texture * NoHealthBar;

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
	int healthsubstract = 0;
	bool EnemyHit = false;







};
