#include "pch.h"
#include "GameLoop.h"
using namespace std;


SDL_Texture* PlayerTex;
SDL_Rect srcR, destR;//W and H for dimension, X and Y for movement!!

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

		quit = false;

	}
	else quit = true; 

	SDL_Surface* tmpSurface = IMG_Load("debug/Dirt.jpg");
	PlayerTex = SDL_CreateTextureFromSurface(renderer, tmpSurface);
	SDL_FreeSurface(tmpSurface);

}

void GameLoop::processInput()
{
	SDL_Event event;
	SDL_PollEvent(&event);
	switch (event.type)

	{
	case SDL_QUIT:
		quit = true;
		break;


	default:
		break;
	}
	
}

void GameLoop::update()
{
	count++;
	destR.h = 32;
	destR.w = 32;
	
	
	cout << count << endl;
}

void GameLoop::render()
{
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, PlayerTex, NULL, &destR);
	SDL_RenderPresent(renderer);
}

void GameLoop::clean()
{
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
	cout << "Game cleaned!" << endl;
}

