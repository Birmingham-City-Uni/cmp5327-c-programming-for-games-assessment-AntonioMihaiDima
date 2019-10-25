#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Wall {
public:




	Wall(SDL_Renderer*);

	void counter();
	void init();
	void processInput(SDL_Event e);
	void update();
	void draw();
	void clean();



	int wallarray[16];
	


private:

	SDL_Texture* WallTex;
	SDL_Renderer * renderer;
	SDL_Rect position;
	
	

};