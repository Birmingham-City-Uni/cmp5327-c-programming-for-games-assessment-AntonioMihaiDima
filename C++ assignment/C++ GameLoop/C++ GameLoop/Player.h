#pragma once
#include <SDL.h>
#include <SDL_image.h>



class Player {
public:
	Player(SDL_Renderer*);

	void init();
	void processInput(SDL_Event e);
	void update();
	void draw();
	void clean();

	float getxpos()
	{
		return xpos;
	}
	float getypos()
	{
		return ypos;
	}
	float getAngle()
	{
		return angle;
	}

protected:

	float angle = 0;
	float xpos = 768;
	float ypos = 384;
	SDL_Rect position;
	SDL_Texture *playertexture;
	SDL_Renderer *renderer;
};
