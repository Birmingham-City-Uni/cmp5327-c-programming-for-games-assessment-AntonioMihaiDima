#ifndef GameLoop_h
#define GameLoop_h


#include <SDL.h>
#include <iostream>


class GameLoop {

public:
	GameLoop();
	~GameLoop();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void processInput();

	void update(); //returns true only if appplication is closed

	void render();

	void clean();

	bool run() {
		return running;
	}


private:
	int count = 0;
	bool running = true;
	SDL_Window* window;
	SDL_Renderer * renderer;

};

#endif /*GameLoop_h*/



