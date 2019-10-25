#include "Wall.h"
#include "pch.h"
#include <stdlib.h> 
using namespace std;


Wall::Wall(SDL_Renderer * renderer)
{
	this->renderer = renderer;
	
}

int wallarray[16];

void Wall::init()
{
	SDL_Surface* brickSurface = IMG_Load("debug/Brick.jpg");
	WallTex = SDL_CreateTextureFromSurface(this->renderer, brickSurface);
	SDL_FreeSurface(brickSurface);
	
	/*for (int i = 0; i < 16; i++)
	{
		wallarray[i] = 50;
	}
	for (int i = 0; i < 16; i++)
	{
		wallarray[i] = rand() % 25 + 1;
		for (int j = 0; j < 16; j++)
			if (wallarray[i] != wallarray[j])
				i -= 1;

	}
	*/
	
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

	/*for (int i = 0; i < 16; i++)
	{
		SDL_Rect randposition = { wallarray[i] * 32, wallarray[i + 1] * 32, 32, 32 };
		SDL_RenderCopy(this->renderer, WallTex, NULL, &randposition);
	}
	*/

}
