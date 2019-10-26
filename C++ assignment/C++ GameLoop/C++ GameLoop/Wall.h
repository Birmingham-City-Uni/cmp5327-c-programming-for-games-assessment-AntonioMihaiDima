#pragma once
#include <SDL.h>
#include <SDL_image.h>


extern int tilearray[16];

class Wall {
public:




	Wall(SDL_Renderer*);

	void counter();
	void init();
	void processInput(SDL_Event e);
	void update();
	void draw();
	void clean();


	

	


private:
	
	SDL_Texture* WallTex;
	SDL_Renderer * renderer;
	SDL_Rect position;
	
	

};