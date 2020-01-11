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

	SDL_Surface * surface2 = IMG_Load("debug/BulletTexture.png");
	this->Bullet = SDL_CreateTextureFromSurface(this->renderer, surface2);
	SDL_FreeSurface(surface2);

	SDL_Surface * surface3 = IMG_Load("debug/BulletTextureAnimated.png");
	this->BulletAnimated = SDL_CreateTextureFromSurface(this->renderer, surface3);
	SDL_FreeSurface(surface3);

	SDL_Surface * surface4 = IMG_Load("debug/PlayerReload.png");
	this->PlayerReload = SDL_CreateTextureFromSurface(this->renderer, surface4);
	SDL_FreeSurface(surface4);
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
	if (EndGame == false)
	{
		//Here we just make sure the player can't control the player sprite until the map is scrolled.
		if (NoMoreEnemies == true)
		{
			upmovement = false;
			downmovement = false;
			leftmovement = false;
			rightmovement = false;
		}


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
							leftdirection = false;
						}
						else if (obstacles[int(xpos / 32)][int(ypos / 32) + 1] == 0)
						{
							if (directionpicked == 2)
							{
								leftdirection = true;
							}
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

						if (leftdirection)
						{
							directionpicked = 2;
							angle = 270;
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

			if (xpos >= 768)
			{
				tilemap->WaveComplete = true;
			}

			if (tilemap->WaveComplete == true)
			{
				if (distancetravelled < 32)
				{
					if (directiontobepicked == false)
					{
						if ((obstacles[int(xpos / 32) - 1][int(ypos / 32)] == 0) && (uppercollision == false))
						{
							angle = 0;
							tilemap->uppercollision = false;
							directionpicked = 0;
							leftdirection = false;
						}
						else if (obstacles[int(xpos / 32)][int(ypos / 32) + 1] == 0)
						{
							if (directionpicked == 2)
							{
								leftdirection = true;
							}
							angle = 90;
							tilemap->uppercollision = true;
							directionpicked = 1;
							uppercollision = true;
						}
						else if (obstacles[int(xpos / 32)][int(ypos / 32) - 1] == 0)
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

						if (leftdirection)
						{
							directionpicked = 2;
							angle = 270;
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

		//Found a bug where when the player travels to the next wave and is on the far right tile (really close to the right set of walls) the character is 2 pixels into the wall tile and when the next level starts the character
		//is thrown out of the map. In this code below the program checks if the player is at that unwanted position and just before the next wave starts pushes the character by 2 pixels to the left. This fixed the bug.
		if ((xpos >= 768) && (ypos == 736) && (tilemap->WaveComplete == false))
			ypos = 734;

		if ((xpos >= 768) && (ypos < 34) && (tilemap->WaveComplete == false))
			ypos = 34;

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
	//Have the player stay in the boundaries of the screen.
	if (xpos <= 0)
		xpos = xpos + 2;
	if (xpos >= 770)
		xpos = xpos - 2;

	//Bullet animation.
	if (SDL_GetTicks() % 1000 <= 500)
	{
		AnimationNumber = 1;
	}

	if (SDL_GetTicks() % 1000 > 500)
	{
		AnimationNumber = 2;
	}
	if (BulletNumber == 0)
	{
		if (SDL_GetTicks() - ReloadTimer > 1250)
		{
			ReloadTimer = SDL_GetTicks();
			if (Reloading)
			{
				Reloading = false;
				BulletNumber = 7;
			}
			else
			{
				Reloading = true;
			}
		}


	}
}

void Player::draw()
{

	
		SDL_Rect position = { ypos, xpos, playerwidth, playerheight };

		SDL_Point * center = NULL;

		if (!Reloading)
		SDL_RenderCopyEx(this->renderer, this->playertexture, 0, &position, angle, center, SDL_FLIP_NONE);
		
		if (Reloading)
		SDL_RenderCopyEx(this->renderer, this->PlayerReload, 0, &position, angle, center, SDL_FLIP_NONE);
	

	for (int j = 23; j > 23 - BulletNumber; j --)
	{
		if (AnimationNumber == 1)
		{
			SDL_Rect BulletRect = { 24 * 32, j * 32, 32, 32 };
			SDL_RenderCopyEx(this->renderer, this->Bullet, 0, &BulletRect, BulletRotation, center, SDL_FLIP_NONE);
		}

		if (AnimationNumber == 2)
		{
			SDL_Rect BulletRect = { 24 * 32, j * 32, 32, 32 };
			SDL_RenderCopyEx(this->renderer, this->BulletAnimated, 0, &BulletRect, BulletRotation, center, SDL_FLIP_NONE);
		}
	}


}

void Player::clean()
{
	SDL_DestroyTexture(this->playertexture);
	SDL_DestroyTexture(this->Bullet);
	SDL_DestroyTexture(this->BulletAnimated);
	SDL_DestroyTexture(this->PlayerReload);
}