#pragma once

#include <SDL_ttf.h>

#include <sstream>
#include "EnemyManager.h"

class EnemyManager;
using namespace std;



class TextRenderer
{
public:

	TextRenderer(SDL_Renderer* renderer, EnemyManager * enemymanager) : renderer(renderer), enemymanager(enemymanager) {};
	void init()
	{	
		if (TTF_Init() == -1)
			cout << "oops";
		font = TTF_OpenFont("arial.ttf", 25);
		White = { 255, 255, 255 };
		//For some reason if i take this cout out the compiler crashes.
		cout << endl;
	}	

	void draw()
	{
		stringstream ScoreString;
		ScoreString << "Score : ";
		if (enemymanager->Scoregained)
		{
			scorenum += 100;
			enemymanager->Scoregained = false;
		}
		auto scorenumstring = to_string(scorenum);
		ScoreString << scorenumstring;
		surfaceMessage = TTF_RenderText_Solid(font, ScoreString.str().c_str(), White);
		Score = SDL_CreateTextureFromSurface(this->renderer, this->surfaceMessage);

		SDL_Rect ScoreRect = { 32, 0 , 100, 50 };
		SDL_RenderCopy(this->renderer, Score, NULL, &ScoreRect);
		//Use those in order not to have leaks in memory.
		SDL_DestroyTexture(Score);
		SDL_FreeSurface(surfaceMessage);		
	}

	void clean()
	{

	}



private:
	SDL_Renderer * renderer;
	SDL_Texture * Score;
	SDL_Surface * surfaceMessage;
	EnemyManager * enemymanager;
	TTF_Font * font;
	int scorenum = 0;
	SDL_Color White;




};

