#include "pch.h"
#include "GameLoop.h"
using namespace std;

GameLoop::GameLoop()
{

}

GameLoop::~GameLoop()
{

}

void GameLoop::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
	int flags = 0;
	if (fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
	{
		cout << "Subsystems Initialized" << endl;
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
		if (window)
		{
			cout << "Window created!" << endl;
		}

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer)
		{
			SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
			cout << "Renderer created!" << endl;
		}

		running = true;

	}
	else running = false;
}

void GameLoop::processInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)

	{
	case SDL_QUIT:
		running = false;
		break;


	default:
		break;
	}
	
}

void GameLoop::update()
{
	count++;
	cout << count << endl;
}

void GameLoop::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderPresent(renderer);
}

void GameLoop::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned!" << endl;
}

