#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "GameLoop.h"

class Player {
public:
	Player(SDL_Renderer*);

	void init();
	void processInput(SDL_Event e);
	void update();
	void draw();
	void clean();


private:


	SDL_Rect position;
	SDL_Texture *playertexture;
	SDL_Renderer *renderer;
};
