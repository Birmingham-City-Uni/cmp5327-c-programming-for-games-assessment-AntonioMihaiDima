#include "Wall.h"
#include "Water.h"
#include "pch.h"
#include <stdlib.h>
#include "time.h"
#include <iostream>
using namespace std;

/*
Water::Water(SDL_Renderer * renderer)
{
	this->renderer = renderer;
}


void Water::init()
{
	SDL_Surface* waterSurface = IMG_Load("debug/Water.jpg");
	WaterTex = SDL_CreateTextureFromSurface(this->renderer, waterSurface);
	SDL_FreeSurface(waterSurface);
}


void Water::processInput(SDL_Event e)
{

}


void Water::update()
{

}

void Water::draw()
{
	for (int i = 24; i < 32; i++)
	{
		SDL_Rect randposition = { tilearray[i] * 32, tilearray[i + 1] * 32, 32, 32 };
		SDL_RenderCopy(this->renderer, WaterTex, NULL, &randposition);
	}
}

void Water::clean()
{

}

*/