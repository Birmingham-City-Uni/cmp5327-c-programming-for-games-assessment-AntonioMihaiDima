#include "pch.h"
#include "GameLoop.h"

GameLoop::GameLoop()
{

}

bool GameLoop::init()
{
	for (int i = 0; i < 256; i++)
	{
		keydown[i] = false;
	}

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

	player = new Player(this->renderer);
	tilemap = new Tilemap(this->renderer);
	tilemap->init();
	player->init();
	bm = new BulletManager(this->renderer, this->player);
	bm->init();

}

bool GameLoop::processInput()
{
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) {
			return false;
		}
		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.scancode < 512)
				keydown[e.key.keysym.scancode] = true;
		}
		if (e.type == SDL_KEYUP)
		{
			if (e.key.keysym.scancode < 512)
				keydown[e.key.keysym.scancode] = false;
		}

		//process any input for game classes here

		tilemap->processInput(e);
		player->processInput(e);
		bm->processInput(keydown);
	}

	return true;
}

void GameLoop::update()
{
	//process updating for game classes here

	
	tilemap->update();
	player->update();
	bm->update();

}

void GameLoop::draw()
{
	SDL_RenderClear(renderer);

	//process drawing for game classes here

	tilemap->draw();
	player->draw();
	bm->draw();

	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

void GameLoop::clean()
{
	//process clean up for game classes here
	tilemap->clean();
	player->clean();
	bm->clean();
	if (player)
	{
		delete player;
		player = nullptr;
	}
	if (tilemap)
	{
		delete tilemap;
		tilemap = nullptr;
	}


}

