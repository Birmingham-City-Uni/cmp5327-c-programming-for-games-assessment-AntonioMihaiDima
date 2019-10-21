// C++ GameLoop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SDL.h>
#include "GameLoop.h"
using namespace std;

GameLoop *game = nullptr;

#undef main

/*
YouTube. (2017). Making A Game #1: Making The Game Loop : C++ And SDL2 Tutorial. [online] 
Available at: https://www.youtube.com/watch?v=44tO977slsU&t=153s [Accessed 17 Oct. 2019].
*/


int main(int argc, char* args[])
{

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	Uint32 frameStart;
	int FrameTime;

	game = new GameLoop();

	game->init("2D Shooter", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, false);

	while (game ->quit == false)
	{

		frameStart = SDL_GetTicks();

		game->processInput();
		game->update();
		game->render();


		FrameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > FrameTime)
		{
			SDL_Delay(frameDelay - FrameTime);
		}
	}

	game->clean();


		return 0;

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
