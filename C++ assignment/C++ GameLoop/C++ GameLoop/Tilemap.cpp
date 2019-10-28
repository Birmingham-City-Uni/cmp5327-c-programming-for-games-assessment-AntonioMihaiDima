#include "Tilemap.h"
#include "pch.h"
#include <stdlib.h>
#include "time.h"
#include <iostream>
using namespace std;

int tilearrayvalues[66];
int tilemaparray[50][25];
bool checkmap = true;
int secondaryposition = 25;
bool numberspicked = false;


Tilemap::Tilemap(SDL_Renderer * renderer)
{
	this -> renderer = renderer;
	
}



void Tilemap::init()
{
		SDL_Surface* tmpSurface = IMG_Load("debug/Dirt.jpg");
		MapTex = SDL_CreateTextureFromSurface(this->renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);

		SDL_Surface* brickSurface = IMG_Load("debug/Brick.jpg");
		WallTex = SDL_CreateTextureFromSurface(this->renderer, brickSurface);
		SDL_FreeSurface(brickSurface);

		SDL_Surface* waterSurface = IMG_Load("debug/Water.jpg");
		WaterTex = SDL_CreateTextureFromSurface(this->renderer, waterSurface);
		SDL_FreeSurface(waterSurface);


		//Here we want to set number 1's for the map array, which later we will use to generate wall textures.
		for (int i = 0; i < 50; i++)
		{
			tilemaparray[i][0] = 1;
			tilemaparray[i][24] = 1;

		}

		//Set initially every other tile to Dirt
		for (int i = 0; i < 50; i++)
			for (int j = 1; j < 24; j++)
				tilemaparray[i][j] = 0;







		//We want to randomise the values for the random number array
		srand(time(0));

		//Firstly we set every element of the array to a value which we won't be using
		for (int i = 0; i < 66; i++)
		{
			tilearrayvalues[i] = -50;
		}

		//Secondly we generate random numbers into a range. The tilemap is 25x32 long, the edges are walls (2x32) so we want a 23 range.
		for (int i = 8; i < 58; i++)
		{
			tilearrayvalues[i] = rand() % 23 + 1;
		}

		//Random numbers for the bottom of the screen
		for (int i = 58; i < 66; i++)
		{
			tilearrayvalues[i] = 26 + rand() % (41 - 26 + 1);
		}

		//Random numbers for the top of the screen
		for (int i = 0; i < 8; i++)
		{
			tilearrayvalues[i] = (rand() % 9 + 1) * -1;
		}


		

		/*for (int i = 0; i < 66; i++)
			cout << tilearrayvalues[i] << " ";
			*/


		
		/*
		wall = new Wall(this->renderer);
		water = new Water(this->renderer);

		*/


		position.x = 0;
		position.y = 0;
		position.h = 32;
		position.w = 32;

		//wall->counter();
	



}


void Tilemap::processInput(SDL_Event e)
{

}


void Tilemap::update()
{
	
	



	


	//Code to destroy the textures that we won't be needing
	/*if (tilemaptexture == false) 
	{
		SDL_DestroyTexture(this->MapTex);
		tilemaptexture = true;
		SDL_Surface* tmpSurface = IMG_Load("debug/Dirt.jpg");
		MapTex = SDL_CreateTextureFromSurface(this->renderer, tmpSurface);
		SDL_FreeSurface(tmpSurface);
	}
		*/

	
}


void Tilemap::draw()
{
	for (int i = 0; i < 25; i++) 
		for (int j = 0; j < 25; j++)

			//array[i][j]

		{
			//SDL_Rect positions orientations are inversed compared to the array's i and j
			SDL_Rect position = { j * 32, i * 32, 32, 32 };

			//Set tiles on the map based on the random numbers from the array
			for (int i = 8; i < 16; i++)
			{
				tilemaparray[tilearrayvalues[i]][tilearrayvalues[i + 1]] = 1;
			}
			for (int i = 16; i < 24; i++)
			{
				tilemaparray[tilearrayvalues[i]][tilearrayvalues[i + 1]] = 2;
			}
			/*for (int i = 16; i < 24; i++)
			{
				tilemaparray[tilearrayvalues[i]][tilearrayvalues[i + 1]] = 1;
			}
			for (int i = 24; i < 32; i++)
			{
				tilemaparray[tilearrayvalues[i]][tilearrayvalues[i + 1]] = 2;
			}
			*/

			//Here we just render the tilemap depending on the array's values
			if (tilemaparray[i][j] == 0)
				SDL_RenderCopy(this->renderer, MapTex, NULL, &position);
			if (tilemaparray[i][j] == 1)
				SDL_RenderCopy(this->renderer, WallTex, NULL, &position);
			if (tilemaparray[i][j] == 2)
				SDL_RenderCopy(this->renderer, WaterTex, NULL, &position);

			//This loop is just to test if we constructed the tilemap right
			//We use the checkmap boolean to make sure that the loop runs only once
			
			
		}

	for (int i = 0; i < 25; i++)
		for (int j = 25; j < 40; j++)
		{
			SDL_Rect secondposition = { j * 32, i * 32, 32, 32 };
			
			//if (checkmap == true)
			{
				int b = 58;
				for (int a = 25; a < 29; a++)
				{
					
					tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] = 1;
					b++;

					//cout << tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] << " ";
				}

				//checkmap = false;
			}
				
			
				
			int b = 62;
				for (int a = 29; a < 33; a++)
				{
					
					tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] = 2;
					b++;
				}

			


			if (tilemaparray[i][j] == 0)
				SDL_RenderCopy(this->renderer, MapTex, NULL, &secondposition);
			if (tilemaparray[i][j] == 1)
				SDL_RenderCopy(this->renderer, WallTex, NULL, &secondposition);
			if (tilemaparray[i][j] == 2)
				SDL_RenderCopy(this->renderer, WaterTex, NULL, &secondposition);

		}




	if (checkmap == true)
	{
		for (int i = 0; i < 50; i++)
		{
			for (int j = 0; j < 25; j++)
			{
				if (j < 24)
					cout << tilemaparray[i][j] << " ";
				if (j == 24)
					cout << tilemaparray[i][j] << endl;
			}

		}
		checkmap = false;


	}

	
}

void Tilemap::clean()
{
	SDL_DestroyTexture(this->MapTex);
}


/*void Player::Init()
{
	SDL_Surface * surface = IMG_Load("Dirt.jpg");
	this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}


void Player::processInput(SDL_Event e)
{

}

void Player::Update()
{

}*/
