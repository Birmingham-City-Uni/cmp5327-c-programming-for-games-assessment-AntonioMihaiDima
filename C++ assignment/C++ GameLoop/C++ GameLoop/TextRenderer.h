#pragma once

#include <SDL_ttf.h>

using namespace std;



class TextRenderer {
public:

	TextRenderer(SDL_Renderer* renderer) : renderer(renderer) {};
	void init()
	{

		TTF_Init();
		font = TTF_OpenFont("arial.ttf", 25);
		SDL_Color White = { 255, 255, 255 };
		surfaceMessage = TTF_RenderText_Solid(font, "Score: ", White);
		Score = SDL_CreateTextureFromSurface(this->renderer, this->surfaceMessage);
		if (Score == NULL)
			cout << "oops";
		SDL_FreeSurface(surfaceMessage);
    }

	void draw()
	{
		SDL_Rect ScoreRect = { 32, 0, 50, 50 };
		SDL_RenderCopy(this->renderer, Score, NULL, &ScoreRect);
	}



private:
	SDL_Renderer * renderer;
	SDL_Texture * Score;
	SDL_Surface * surfaceMessage;
	TTF_Font * font;



};

