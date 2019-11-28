#include "Player.h"





bool uppercollision = false;
bool leftcollision = false;
bool bottomcollision = false;
bool rightcollision = false;
int lastkeypressed = 0;
int previouskey = 0;



bool collsiondetected = false;



Player::Player(SDL_Renderer* renderer, Tilemap * tilemap)
{
	this->renderer = renderer;
	this->tilemap = tilemap;
}

void Player::init()
{
	SDL_Surface * surface = IMG_Load("debug/PlayerTexture.png");
	this->playertexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);

/*	SDL_Surface * enemysurface = IMG_Load("debug/EnemyTexture.png");
	this->enemytexture = SDL_CreateTextureFromSurface(this->renderer, enemysurface);
	SDL_FreeSurface(enemysurface);
	*/




	//obstacles[xslot][yslot] = 3;


}

void Player::processInput(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_w)
		{
			upmovement = true;
			downmovement = false;
			leftmovement = false;
			rightmovement = false;
		}
		if (e.key.keysym.sym == SDLK_s)
		{
			upmovement = false;
			downmovement = true;
			leftmovement = false;
			rightmovement = false;
		}
		if (e.key.keysym.sym == SDLK_a)
		{
			upmovement = false;
			downmovement = false;
			leftmovement = true;
			rightmovement = false;
		}
		if (e.key.keysym.sym == SDLK_d)
		{
			upmovement = false;
			downmovement = false;
			leftmovement = false;
			rightmovement = true;
		}
	}
	if (e.type == SDL_KEYUP)
	{
		if (e.key.keysym.sym == SDLK_w)
		{
			upmovement = false;
		}
		if (e.key.keysym.sym == SDLK_s)
		{
			downmovement = false;
		}
		if (e.key.keysym.sym == SDLK_a)
		{
			leftmovement = false;
		}
		if (e.key.keysym.sym == SDLK_d)
		{
			rightmovement = false;
		}
	}
	

	
}

void Player::update()
{
	//Here we just make sure the player can't control the player sprite until the map is scrolled.
	if (NoMoreEnemies == true)
	{
		upmovement = false;
		downmovement = false;
		leftmovement = false;
		rightmovement = false;
	}




	if (tilemap->isMoving == false)
		for (int i = 0; i < 26; i++)
			for (int j = 0; j < 26; j++)
			{
				obstacles[i][j] = tilemap->tilemaparray[i][j];
			}


	xslot = xpos / 32 + 1;
	yslot = ypos / 32 + 1;

	uppercollision = false;
	bottomcollision = false;
	leftcollision = false;
	rightcollision = false;

	if (NoMoreEnemies == false)
	{
		if ((obstacles[xslot - 1][yslot] == 1) || (obstacles[xslot - 1][yslot] == 2))
		{
			if (angle == 0)
			{
				uppercollision = true;
				xpos = (xslot) * 32 + 2;
			}
			if (angle == 90)
			{
				rightcollision = true;
				ypos = (yslot - 1) * 32 - 2;
				std::cout << "Collision" << std::endl;
			}

		}
		if ((obstacles[xslot - 1][yslot - 1] == 1) || (obstacles[xslot - 1][yslot - 1] == 2))
		{
			if (angle == 0)
			{
				uppercollision = true;
				xpos = (xslot) * 32 + 2;
			}
			if (angle == 270)
			{
				leftcollision = true;
				ypos = (yslot) * 32 + 2;
			}
		}
		if ((obstacles[xslot][yslot] == 1) || (obstacles[xslot][yslot] == 2))
		{
			if (angle == 180)
			{
				bottomcollision = true;
				xpos = (xslot - 1) * 32 - 2;
			}
			if (angle == 90)
			{
				rightcollision = true;
				ypos = (yslot - 1) * 32 - 2;
			}
		}
		if ((obstacles[xslot][yslot - 1] == 1) || (obstacles[xslot][yslot - 1] == 2))
		{
			if (angle == 180)
			{
				bottomcollision = true;
				xpos = (xslot - 1) * 32 - 2;
			}
			if (angle == 270)
			{
				leftcollision = true;
				ypos = (yslot) * 32 + 2;
			}
		}
	}

	if (NoMoreEnemies == true)
	{

		//Here we check if there's any offset from a perfect 32 division. We use this to prepare our player for down movement.
		if (perfectxpos == false)
			{
				ypos = ypos / 32 * 32;
				xpos = xpos / 32 * 32;
				angle = 180;
				perfectxpos = true;


			}



		if (xpos < 768)
		{
			if (distancetravelled < 32)
			{
				if (directiontobepicked == false)
				{
					if ((obstacles[int(xpos / 32) + 1][int(ypos / 32)] == 0) && (bottomcollision == false))
					{
						directionpicked = 0;
						angle = 180;
					}
					else if (obstacles[int(xpos / 32)][int(ypos / 32) + 1] == 0)
					{
						directionpicked = 1;
						bottomcollision = false;
						angle = 90;
					}
					else if (obstacles[int(xpos / 32)][int(ypos / 32) - 1] == 0)
					{
						directionpicked = 2;
						bottomcollision = false;
						angle = 270;
					}
					else
					{
						directionpicked = 3;
						bottomcollision = true;
						angle = 0;
					}

					directiontobepicked = true;

				}
				if (directionpicked == 0)
				{
					xpos += 2;
				}
				if (directionpicked == 1)
				{
					ypos += 2;
				}
				if (directionpicked == 2)
				{
					ypos -= 2;
				}
				if (directionpicked == 3)
				{
					xpos -= 2;
				}



			}

			distancetravelled += 2;


			if (distancetravelled == 32)
			{
				directiontobepicked = false;
				distancetravelled = 0;
			}



		}
		//Now the player is at the bottom position
		if (xpos == 768)
		{
			tilemap->WaveComplete = true;
		}

		if (tilemap->WaveComplete == true)
		{
			if (distancetravelled < 32)
			{
				if (directiontobepicked == false)
				{
					if ((tilemap->tilemaparray[int(xpos / 32) - 1][int(ypos / 32)] == 0) && (uppercollision == false))
					{
						angle = 0;
						tilemap->uppercollision = false;
						directionpicked = 0;
					}
					else if (tilemap->tilemaparray[int(xpos / 32)][int(ypos / 32) + 1] == 0)
					{
						angle = 90;
						tilemap->uppercollision = true;
						directionpicked = 1;
						uppercollision = true;					
					}
					else if (tilemap->tilemaparray[int(xpos / 32)][int(ypos / 32) - 1] == 0)
					{
						angle = 270;
						tilemap->uppercollision = true;
						directionpicked = 2;
						uppercollision = true;
					}
					else
					{
						angle = 180;
						tilemap->uppercollision = true;
						directionpicked = 3;
						uppercollision = true;
					}
					directiontobepicked = true;
				}
				if (directionpicked == 0)
				{
					xpos -= 2;
				}
				if (directionpicked == 1)
				{
					ypos += 2;
				}
				if (directionpicked == 2)
				{
					ypos -= 2;
				}
				if (directionpicked == 3)
				{
					xpos += 2;
				}
			}
			distancetravelled += 2;


			if (distancetravelled == 32)
			{
				directiontobepicked = false;
				distancetravelled = 0;
			}
		}
	}


	//if ((upmovement == true) && (uppercollision == false))
	if (upmovement && !uppercollision)
	{

		{
			xpos -= 2;
			angle = 0;
		}
	}
	if (downmovement && !bottomcollision)
	{

		{
			xpos += 2;
			angle = 180;
		}
	}
	if (leftmovement && !leftcollision)
	{

		{
			ypos -= 2;
			angle = 270;
		}
	}
	if (rightmovement && !rightcollision)
	{

		{
			ypos += 2;
			angle = 90;
		}
	}




}

void Player::draw()
{




	/*if ((tilemap->tilemaparray[int(xpos / 32)][int(ypos / 32)] == 1) || (tilemap->tilemaparray[int(xpos / 32)][int(ypos / 32)] == 2) || (tilemap->tilemaparray[int((xpos + 32) / 32)][int((ypos + 32) / 32)] == 2) || (tilemap->tilemaparray[int((xpos + 32) / 32)][int((ypos + 32) / 32)] == 1) || (tilemap->tilemaparray[int((xpos + 32) / 32)][int(ypos / 32)] == 1) || (tilemap->tilemaparray[int((xpos + 32) / 32)][int(ypos / 32)] == 2) || (tilemap->tilemaparray[int(xpos / 32)][int((ypos + 32) / 32)] == 1) || (tilemap->tilemaparray[int(xpos / 32)][int((ypos + 32) / 32)] == 2))
	{


		if (upmovement == true)
		{
			upmovement = false;
			collisionnumber = 1;
		}
		if (downmovement == true)
		{
			downmovement = false;
			collisionnumber = 2;
		}
		if (leftmovement == true)
		{
			leftmovement = false;
			collisionnumber = 3;
		}
		if (rightmovement == true)
		{
			rightmovement = false;
			collisionnumber = 4;
		}



	}
	else if ((tilemap->tilemaparray[int(xpos / 32)][int(ypos / 32)] == 0))
	{
		collisionnumber = 0;
	}
	*/




	SDL_Rect position = { ypos, xpos, playerwidth, playerheight };
	SDL_Rect enemyposition = { 64, 0, 32, 32 };



	SDL_Point * center = NULL;

	//SDL_RenderCopyEx(this->renderer, this->enemytexture, 0, &enemyposition, angle, center, SDL_FLIP_NONE);

	SDL_RenderCopyEx(this->renderer, this->playertexture, 0, &position, angle, center, SDL_FLIP_NONE);

	//I put it here for testing, will move it in a better place later.
	//if (DestroyEnemy == true)
		//SDL_DestroyTexture(this->enemytexture);





}

void Player::clean()
{
	SDL_DestroyTexture(this->playertexture);
	//SDL_DestroyTexture(this->enemytexture);
}