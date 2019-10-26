#include "Wall.h"
#include "pch.h"
#include <stdlib.h>
#include "time.h"
#include <iostream>
using namespace std;


int tilearray[16];

Wall::Wall(SDL_Renderer * renderer)
{
	this->renderer = renderer;
	
}



void Wall::counter()
{

	srand(time(0));

	for (int i = 0; i < 16; i++)
	{
		tilearray[i] = 50;
	}
	for (int i = 0; i < 16; i++)
	{
		tilearray[i] = rand() % 23 + 1;
		
		/*for (int j = 0; j < 10; j++)
		{
			if (wallarray[i] == wallarray[j])

				i = i - 1;
			break;
		}
		*/
				

	}
}

void Wall::init()
{
	SDL_Surface* brickSurface = IMG_Load("debug/Brick.jpg");
	WallTex = SDL_CreateTextureFromSurface(this->renderer, brickSurface);
	SDL_FreeSurface(brickSurface);
	

	
}


void Wall::processInput(SDL_Event e)
{

}

void Wall::update()
{

}

void Wall::draw()
{
	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 25; j++)
	{
		SDL_Rect position = { i * 768, j * 32, 32, 32 };
		SDL_RenderCopy(this->renderer, WallTex, NULL, &position);
		
	}

		for (int i = 0; i < 8; i++)
		{
			SDL_Rect randposition = { tilearray[i] * 32, tilearray[i + 1] * 32, 32, 32 };
			SDL_RenderCopy(this->renderer, WallTex, NULL, &randposition);
		}
	

}

