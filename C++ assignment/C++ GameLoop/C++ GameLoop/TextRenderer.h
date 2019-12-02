#pragma once

#include <SDL_ttf.h>

#include <sstream>
#include "EnemyManager.h"
#include <string>

class EnemyManager;
using namespace std;



class TextRenderer
{
public:

	TextRenderer(SDL_Renderer* renderer, EnemyManager * enemymanager) : renderer(renderer), enemymanager(enemymanager) {};	

	void init()
	{
		font = TTF_OpenFont("arial.ttf", 25);
		stringstream ScoreString;
		ScoreString << "Score : ";
		auto scorenumstring = to_string(scorenum);
		ScoreString << scorenumstring;
		surfaceMessage = TTF_RenderText_Solid(font, ScoreString.str().c_str(), { 255,255,255 });
		Score = SDL_CreateTextureFromSurface(this->renderer, this->surfaceMessage);
	}

	void draw()
	{
		if (enemymanager->Scoregained)
		{
			SDL_DestroyTexture(Score);
			SDL_FreeSurface(surfaceMessage);
			scorenum += 100;
			stringstream ScoreString;
			ScoreString << "Score : ";
			auto scorenumstring = to_string(scorenum);
			ScoreString << scorenumstring;
			surfaceMessage = TTF_RenderText_Solid(font, ScoreString.str().c_str(), { 255,255,255 });
			Score = SDL_CreateTextureFromSurface(this->renderer, this->surfaceMessage);
			enemymanager->Scoregained = false;
		}

		SDL_Rect ScoreRect = { 32, 0 , 100, 50 };
		SDL_RenderCopy(this->renderer, Score, NULL, &ScoreRect);


	}

	void clean()
	{
		//Use those in order not to have leaks in memory.
		TTF_CloseFont(font);
		SDL_DestroyTexture(Score);
		SDL_FreeSurface(surfaceMessage);
	}



private:
	SDL_Renderer * renderer;
	SDL_Texture * Score;
	SDL_Surface * surfaceMessage;
	EnemyManager * enemymanager;
	TTF_Font * font;
	int scorenum = 0;





};

