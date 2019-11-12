#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameLoop.h"



extern int tilearrayvalues[48]; //An array which stores a random number sequence for positioning
extern int tilemaparray[50][25]; //Bidimentional array to store the map tiles



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
	SDL_Texture* WallTex;
	SDL_Texture* WaterTex;
	SDL_Renderer * renderer;
	SDL_Rect position;
	SDL_Rect secondposition;
	SDL_Rect thirdposition;
	const Uint8 * keystate = SDL_GetKeyboardState(NULL);
	
	
};

