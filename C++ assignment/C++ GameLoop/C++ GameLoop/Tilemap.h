#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "Wall.h"
#include "Water.h"


class Tilemap {
public:




	Tilemap(SDL_Renderer*);

	void init();
	void processInput(SDL_Event e);
	void update();
	void draw();
	void clean();



private:

	SDL_Texture* MapTex;
	SDL_Renderer * renderer;
	SDL_Rect position;
	Wall * wall;
	Water * water;
	
	
};