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

		stringstream WaveString;
		WaveString << "Wave ";
		auto WaveNumString = to_string(WaveNum);
		WaveString << WaveNumString;
		WaveSurface = TTF_RenderText_Solid(font, WaveString.str().c_str(), { 255, 255, 255, 255 });
		Wave = SDL_CreateTextureFromSurface(this->renderer, this->WaveSurface);
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
		if((enemymanager->bulletmanager->player->EndGame == true)&&(!EfficiencyBool))
		{
			EndGameSurface = TTF_RenderText_Solid(font, "Game Over", { 255,255,255 });
			EndGame = SDL_CreateTextureFromSurface(this->renderer, this->EndGameSurface);
			EfficiencyBool = true;
		}

		if ((enemymanager->bulletmanager->player->NoMoreEnemies) && (!WaveTextChanged))
		{
			SDL_DestroyTexture(Wave);
			SDL_FreeSurface(WaveSurface);
			string WaveString;
			WaveString = "Travelling to the next wave";
			WaveSurface = TTF_RenderText_Solid(font, WaveString.c_str(), { 255, 255, 255, 255 });
			Wave = SDL_CreateTextureFromSurface(this->renderer, this->WaveSurface);

			WaveTextChanged = true;
			
		}
		if ((enemymanager->bulletmanager->player->NoMoreEnemies == false) && (WaveTextChanged))
		{
			WaveNum += 1;
			WaveTextChanged = false;
			SDL_DestroyTexture(Wave);
			SDL_FreeSurface(WaveSurface);

			stringstream WaveString;
			WaveString << "Wave ";
			auto WaveNumString = to_string(WaveNum);
			WaveString << WaveNumString;
			WaveSurface = TTF_RenderText_Solid(font, WaveString.str().c_str(), { 255, 255, 255, 255 });
			Wave = SDL_CreateTextureFromSurface(this->renderer, this->WaveSurface);

		}

		SDL_Rect ScoreRect = { 32, 0 , 100, 50 };
		SDL_RenderCopy(this->renderer, Score, NULL, &ScoreRect);
		SDL_Rect GameOverRect = { 250, 316, 300, 100 };
		SDL_RenderCopy(this->renderer, EndGame, NULL, &GameOverRect);
		if (enemymanager->bulletmanager->player->NoMoreEnemies == false)
		{
			SDL_Rect WaveRect = { 350, 0, 100, 50 };
			SDL_RenderCopy(this->renderer, Wave, NULL, &WaveRect);
		}
		if (enemymanager->bulletmanager->player->NoMoreEnemies)
		{
			SDL_Rect WaveRect = { 250, 0, 300, 50 };
			SDL_RenderCopy(this->renderer, Wave, NULL, &WaveRect);
		}

	}

	void clean()
	{
		//Use those in order not to have leaks in memory.
		TTF_CloseFont(font);
		SDL_DestroyTexture(Score);
		SDL_FreeSurface(surfaceMessage);
		SDL_DestroyTexture(EndGame);
		SDL_FreeSurface(EndGameSurface);
		SDL_DestroyTexture(Wave);
		SDL_FreeSurface(WaveSurface);
	}



private:
	SDL_Renderer * renderer;
	SDL_Texture * Score;
	SDL_Surface * surfaceMessage;
	SDL_Texture * EndGame;
	SDL_Surface * EndGameSurface;
	SDL_Texture * Wave;
	SDL_Surface * WaveSurface;
	EnemyManager * enemymanager;
	TTF_Font * font;
	int scorenum = 0;
	bool EfficiencyBool = false;
	bool WaveTextChanged = false;
	int WaveNum = 1;





};

