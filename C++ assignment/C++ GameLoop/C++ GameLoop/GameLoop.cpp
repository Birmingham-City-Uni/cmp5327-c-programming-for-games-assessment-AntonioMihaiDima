#include "pch.h"
#include "GameLoop.h"

GameLoop::GameLoop()
{

}

bool GameLoop::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cerr << "Could not initialise SDL: " << SDL_GetError();
		return false;
	}
	window = SDL_CreateWindow(
		"2D Shooter",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		800, 800,
		SDL_WINDOW_SHOWN
	);

	if (!window) {
		std::cerr << "Could not create SDL window: " << SDL_GetError();
		return false;
	}

	// Create renderer
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cout << "Error creating renderer:" << SDL_GetError() << std::endl;
		return false;
	}

	//process initialisation for game classes here

	tilemap = new Tilemap(this->renderer);
	tilemap->init();

}

bool GameLoop::processInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}

		//process any input for game classes here

		tilemap->processInput(e);
	}

	return true;
}

void GameLoop::update()
{
	//process updating for game classes here

	tilemap->update();

}

void GameLoop::draw()
{
	SDL_RenderClear(renderer);

	//process drawing for game classes here

	tilemap->draw();

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

void GameLoop::clean()
{
	//process clean up for game classes here
	tilemap->clean();
	if (tilemap)
	{
		delete tilemap;
		tilemap = nullptr;
	}


}

