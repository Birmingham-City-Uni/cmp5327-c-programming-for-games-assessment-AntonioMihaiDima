// C++ GameLoop.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SDL.h>
using namespace std;

#undef main

/*
Moodle.bcu.ac.uk. (2019). CMP5327 C++ Programming For Games A S1 2019/0 SDL Bouncing ball template project. [online] 
Available at: https://moodle.bcu.ac.uk/course/view.php?id=76001 [Accessed 5 Oct. 2019].
*/
static bool quitting = false;
//Calculate framerate
static Uint32 lastFrameStartTime = 0;
//The last event SDL recieved.
static SDL_Event e;
//Initialise an empty window.
static SDL_Window* window = nullptr;
//Surface of the window where we can render.
static SDL_Surface* screenSurface = nullptr;

void Update()
{
	//Get the time at the start of this frame,
		//so we can determine the right delay to apply
		//to force it to end 17ms later (ensuring 60fps).
	lastFrameStartTime = SDL_GetTicks();

	//Handle each event picked up by SDL in turn.
	while (SDL_PollEvent(&e))
	{
		//In this program, the only event we're
		//worried about is when the user closes the window.
		if (e.type == SDL_QUIT) quitting = true;
	}
}

void Render()
{
	//Always keep this at the end of your game loop! It syncs the
		//surface, which you can't see, with the window, which you can.
	SDL_UpdateWindowSurface(window);

	//If the frame took less than 17ms, delay it until 17ms has passed
	//(enforced 60fps).
	if (SDL_GetTicks() - lastFrameStartTime < 17)
		SDL_Delay(17 - (SDL_GetTicks() - lastFrameStartTime));
}

void Input()
{
	//Initialise the program. If there is an error quit the game.
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		cerr << "Could not initialise SDL: " << SDL_GetError();
		quitting = true;
	}

	//Create window to render program
	window = SDL_CreateWindow("GameLoop", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		cerr << "Could not create SDL window: " << SDL_GetError();
		quitting = true;
	}

	//Window rendering surface
	screenSurface = SDL_GetWindowSurface(window);
}





int main(int argc, char* args[])
{
	Input();

	while (!quitting) 
	{
		
		Update();
		
		Render();
	}

	SDL_DestroyWindow(window);
	SDL_Quit();

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
