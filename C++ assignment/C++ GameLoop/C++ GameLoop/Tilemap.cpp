#include "Tilemap.h"
#include "pch.h"
#include <stdlib.h>
#include "time.h"
#include <iostream>
using namespace std;

bool checkmap = true;
int secondaryposition = 25;
bool numberspicked = false;
bool randomtilesassigned = false;
int DownwardsMovementValue = 0;
bool MovingUp = false;
bool TilesToBeChanged = false;

int toprenderingvalue = 1;
bool halfpicker = true;






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
		for (int i = 0; i < 48; i++)
		{
			tilearrayvalues[i] = -50;
		}

		//Secondly we generate random numbers into a range. The tilemap is 25x32 long, the edges are walls (2x32) so we want a 23 range.
		for (int i = 8; i < 40; i++)
		{
			tilearrayvalues[i] = rand() % 23 + 1;
		}

		//Random numbers for the bottom of the screen
		for (int i = 40; i < 48; i++)
		{
			tilearrayvalues[i] = 26 + (rand() % 16);
		}

		//Random numbers for the top of the screen
		for (int i = 0; i < 8; i++)
		{
			tilearrayvalues[i] = 44 + (rand() % 5);
		}


		

		/*for (int i = 0; i < 66; i++)
			cout << tilearrayvalues[i] << " ";
			*/


		
		/*
		wall = new Wall(this->renderer);
		water = new Water(this->renderer);

		*/


		/*position.x = 0;
		position.y = 0;
		position.h = 32;
		position.w = 32;
		*/

		//wall->counter();
	



}


void Tilemap::processInput(SDL_Event e)
{




}


void Tilemap::update()
{
	if (WaveComplete == true)
	{
		if (uppercollision == false)
		{
			isMoving = true;
		}
		else
		{
			isMoving = false;
		}
	}
	else
	{
		isMoving = false;
	}



	if (isMoving == true)
	{
		DownwardsMovementValue += 2;
	}

	if (randomtilesassigned == false)
	{
		//Set tiles on the map based on the random numbers from the array
		for (int i = 8; i < 16; i++)
		{
			tilemaparray[tilearrayvalues[i]][tilearrayvalues[i + 1]] = 1;
		}
		for (int i = 16; i < 24; i++)
		{
			tilemaparray[tilearrayvalues[i]][tilearrayvalues[i + 1]] = 2;
		}

		{
			int b = 40;
			for (int a = 24; a < 28; a++)
			{

				tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] = 1;
				b++;

				//cout << tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] << " ";
			}

			//checkmap = false;
		}



		int b = 44;
		for (int a = 28; a < 32; a++)
		{

			tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] = 2;
			b++;
		}

		{
			int c = 0;
			for (int d = 32; d < 36; d++)
			{
				tilemaparray[tilearrayvalues[c]][tilearrayvalues[d]] = 1;
				c++;
			}
		}

		{
			int c = 4;
			for (int d = 36; d < 40; d++)
			{
				tilemaparray[tilearrayvalues[c]][tilearrayvalues[d]] = 2;
				c++;
			}
		}

		randomtilesassigned = true;
	}

	if (DownwardsMovementValue >= 32)
	{
		DownwardsMovementValue = 0;
		TilesToBeChanged = true;
	}

	if (TilesToBeChanged == true)
	{

				//here we move the top of the tiles onto the screen view
				for (int i = 0; i < 50; i++)
				{
					for (int j = 0; j < 25; j++)
					{
						tilemaparraymodified[i+1][j] = tilemaparray[i][j];
					}
				}


		
				for (int j = 0; j < 25; j++)
				{
					tilemaparraymodified[0][j] = tilemaparray[49][j];

				}
			

		for (int i = 0; i < 50; i++)
			for (int j = 0; j < 25; j++)
				tilemaparray[i][j] = tilemaparraymodified[i][j];

		TilesToBeChanged = false;
		mainwindowcounter++;

	}

	if (mainwindowcounter == 25)
	{
		if (halfpicker == true)
		{
			for (int i = 25; i < 50; i++)
				for (int j = 1; j < 24; j++)
				{
					tilemaparray[i][j] = 0;
				}


			for (int i = 24; i < 40; i++)
			{
				tilearrayvalues[i] = rand() % 23 + 1;
			}
			for (int i = 40; i < 48; i++)
			{
				tilearrayvalues[i] = 26 + (rand() % 16);
			}
			for (int i = 0; i < 8; i++)
			{
				tilearrayvalues[i] = 44 + (rand() % 5);
			}



			{
				int b = 40;
				for (int a = 24; a < 28; a++)
				{

					tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] = 1;
					b++;

					//cout << tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] << " ";
				}

				//checkmap = false;
			}



			int b = 44;
			for (int a = 28; a < 32; a++)
			{

				tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] = 2;
				b++;
			}

			{
				int c = 0;
				for (int d = 32; d < 36; d++)
				{
					tilemaparray[tilearrayvalues[c]][tilearrayvalues[d]] = 1;
					c++;
				}
			}

			{
				int c = 4;
				for (int d = 36; d < 40; d++)
				{
					tilemaparray[tilearrayvalues[c]][tilearrayvalues[d]] = 2;
					c++;
				}
			}
		}

		if (halfpicker == false)
		{
			for (int i = 25; i < 50; i++)
				for (int j = 1; j < 24; j++)
				{
					tilemaparray[i][j] = 0;
				}


			for (int i = 24; i < 40; i++)
			{
				tilearrayvalues[i] = rand() % 23 + 1;
			}
			for (int i = 40; i < 48; i++)
			{
				tilearrayvalues[i] = 26 + (rand() % 16);
			}
			for (int i = 0; i < 8; i++)
			{
				tilearrayvalues[i] = 44 + (rand() % 5);
			}



			{
				int b = 40;
				for (int a = 24; a < 28; a++)
				{

					tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] = 1;
					b++;

					//cout << tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] << " ";
				}

				//checkmap = false;
			}



			int b = 44;
			for (int a = 28; a < 32; a++)
			{

				tilemaparray[tilearrayvalues[b]][tilearrayvalues[a]] = 2;
				b++;
			}

			{
				int c = 0;
				for (int d = 32; d < 36; d++)
				{
					tilemaparray[tilearrayvalues[c]][tilearrayvalues[d]] = 1;
					c++;
				}
			}

			{
				int c = 4;
				for (int d = 36; d < 40; d++)
				{
					tilemaparray[tilearrayvalues[c]][tilearrayvalues[d]] = 2;
					c++;
				}
			}
		}

		mapscrolled = true;
		mainwindowcounter = 0;
		halfpicker = !halfpicker;
	}

}


void Tilemap::draw()
{
	for (int i = 0; i < 25; i++) 
		for (int j = 0; j < 25; j++)

		{
			//SDL_Rect positions orientations are inversed compared to the array's i and j
			SDL_Rect firstposition = { j * 32, i * 32 + DownwardsMovementValue, 32, 32};


			//Here we just render the tilemap depending on the array's values
			if (tilemaparray[i][j] == 0)
				SDL_RenderCopy(this->renderer, MapTex, NULL, &firstposition);
			if (tilemaparray[i][j] == 1)
				SDL_RenderCopy(this->renderer, WallTex, NULL, &firstposition);
			if (tilemaparray[i][j] == 2)
				SDL_RenderCopy(this->renderer, WaterTex, NULL, &firstposition);

			//This loop is just to test if we constructed the tilemap right
			//We use the checkmap boolean to make sure that the loop runs only once
			
			
		}

	/*for (int i = 25; i < 40; i++)
		for (int j = 0; j < 25; j++)
		{
			SDL_Rect secondposition = { j * 32, i * 32 + DownwardsMovementValue, width, height };
			

			


			if (tilemaparray[i][j] == 0)
				SDL_RenderCopy(this->renderer, MapTex, NULL, &secondposition);
			if (tilemaparray[i][j] == 1)
				SDL_RenderCopy(this->renderer, WallTex, NULL, &secondposition);
			if (tilemaparray[i][j] == 2)
				SDL_RenderCopy(this->renderer, WaterTex, NULL, &secondposition);

		}
		*/

	for (int i = 49; i > 39; i--)
	{
		

		for (int j = 0; j < 25; j++)
		{

			//j should stay positive to render sprites in the same 25 tiles horizontal range.
			SDL_Rect thirdposition = { j * 32, -1 * toprenderingvalue * 32 + DownwardsMovementValue, width, height};



			if (tilemaparray[i][j] == 0)
				SDL_RenderCopy(this->renderer, MapTex, NULL, &thirdposition);
			if (tilemaparray[i][j] == 1)
				SDL_RenderCopy(this->renderer, WallTex, NULL, &thirdposition);
			if (tilemaparray[i][j] == 2)
				SDL_RenderCopy(this->renderer, WaterTex, NULL, &thirdposition);
			
		}
		toprenderingvalue++;
	}
	if (toprenderingvalue == 11)
		toprenderingvalue = 1;




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
	SDL_DestroyTexture(this->WaterTex);
	SDL_DestroyTexture(this->WallTex);
}

