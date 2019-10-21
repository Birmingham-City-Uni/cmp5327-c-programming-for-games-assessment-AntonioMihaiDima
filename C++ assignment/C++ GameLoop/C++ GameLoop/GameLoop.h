#ifndef GameLoop_h
#define GameLoop_h


#include <SDL.h>
#include <iostream>
#include "SDL_image.h"


class GameLoop {

public:
	GameLoop();
	~GameLoop();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void processInput();

	void update(); //returns true only if appplication is closed

	void render();

	void clean();

	bool quit = false;


private:
	int count = 0;
	SDL_Window* window;
	SDL_Renderer * renderer;

};

#endif /*GameLoop_h*/



