#pragma once
#include <SDL.h>
#include <SDL_image.h>


class Player {
public:


	Player(SDL_Renderer*);

	void Init();
	void processInput(SDL_Event e);
	void Update();
	void Draw();
	void Clean();



private:
	SDL_Texture* texture;
	SDL_Renderer* renderer;
};