#include "Player.h"




bool upmovement = false;
bool downmovement = false;
bool leftmovement = false;
bool rightmovement = false;
bool uppercollision = false;
bool leftcollision = false;
bool bottomcollision = false;
bool rightcollision = false;
int collisionnumber = 0;


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

	SDL_Surface * enemysurface = IMG_Load("debug/EnemyTexture.png");
	this->enemytexture = SDL_CreateTextureFromSurface(this->renderer, enemysurface);
	SDL_FreeSurface(enemysurface);




	//obstacles[xslot][yslot] = 3;


}

void Player::processInput(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_w)
		{
			//if (collisionnumber != 1)
			upmovement = true;
		}
		if (e.key.keysym.sym == SDLK_s)
		{
			//if (collisionnumber != 2)
			downmovement = true;
		}
		if (e.key.keysym.sym == SDLK_a)
		{
			//if (collisionnumber != 3)
			leftmovement = true;
		}
		if (e.key.keysym.sym == SDLK_d)
		{
			//if (collisionnumber != 4)
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

	if (tilemap->isMoving == false)
	for (int i = 0; i < 26; i++)
		for (int j = 0; j < 26; j++)
		{
			obstacles[i][j] = tilemap->tilemaparray[i][j];
		}


	xslot = xpos/32 + 1;
	yslot = ypos/32 + 1;

	uppercollision = false;
	bottomcollision = false;
	leftcollision = false;
	rightcollision = false;


	if ((obstacles[xslot - 1][yslot] == 1) || (obstacles[xslot - 1][yslot] == 2))
	{
		if (angle == 0)
		{
			uppercollision = true;
			xpos = (xslot) * 32 + 8;
		}

		if (angle == 45)
		{
			xpos = (xslot) * 32 + 8;
			ypos = (yslot - 1) * 32 - 8;

		}
	}
	if ((obstacles[xslot - 1][yslot - 1] == 1) || (obstacles[xslot - 1][yslot - 1] == 2))
	{
		if (angle == 0)
		{
			uppercollision = true;
			xpos = (xslot) * 32 + 8;
		}
	}
	if ((obstacles[xslot][yslot] == 1) || (obstacles[xslot][yslot] == 2))
	{
		if (angle == 180)
		{
			bottomcollision = true;
			xpos = (xslot -1) * 32 - 8;
		}
	}
	if ((obstacles[xslot][yslot - 1] == 1) || (obstacles[xslot][yslot - 1] == 2))
	{
		if (angle == 180)
		{
			bottomcollision = true;
			xpos = (xslot - 1) * 32 - 8;
		}
	}

	if ((obstacles[xslot][yslot] == 1) || (obstacles[xslot][yslot] == 2))
	{
		if (angle == 90)
		{
			rightcollision = true;
			ypos = (yslot - 1) * 32 - 8;
		}
	}
	if ((obstacles[xslot - 1][yslot] == 1) || (obstacles[xslot - 1][yslot] == 2))
	{
		if (angle == 90)
		{
			rightcollision = true;
			ypos = (yslot - 1) * 32 - 8;
			std::cout << "Collision" << std::endl;
		}
	}
	if ((obstacles[xslot - 1][yslot - 1] == 1) || (obstacles[xslot - 1][yslot - 1] == 2))
	{
		if (angle == 270)
		{
			leftcollision = true;
			ypos = (yslot) * 32 + 8;
		}
	}
	if ((obstacles[xslot][yslot - 1] == 1) || (obstacles[xslot][yslot - 1] == 2))
	{
		if (angle == 270)
		{
			leftcollision = true;
			ypos = (yslot) * 32 + 8;
		}
	}



	
	//if ((upmovement == true) && (uppercollision == false))
	if(upmovement && !uppercollision)
	{

		{
			xpos -= 3;
			angle = 0;
		}
	}
	if (downmovement && !bottomcollision )
	{

		{
			xpos += 3;
			angle = 180;
		}
	}
	if (leftmovement && !leftcollision)
	{

		{
			ypos -= 3;
			angle = 270;
		}
	}
	if (rightmovement && !rightcollision)
	{

		{
			ypos += 3;
			angle = 90;
		}
	}

	if ((upmovement == true) && (leftmovement == true))
	{
		angle = 315;
	}

	if ((upmovement == true) && (rightmovement == true))
	{
		angle = 45;
	}

	if ((downmovement == true) && (leftmovement == true))
	{
		angle = 225;
	}

	if ((downmovement == true) && (rightmovement == true))
	{
		angle = 135;
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
	



	SDL_Rect position = { ypos, xpos, playerwidth, playerheight};
	SDL_Rect enemyposition = { 64, 0, 32, 32 };



	SDL_Point * center = NULL;

	SDL_RenderCopyEx(this->renderer, this->enemytexture, 0, &enemyposition, angle, center, SDL_FLIP_NONE);

	SDL_RenderCopyEx(this->renderer, this->playertexture, 0, &position, angle, center, SDL_FLIP_NONE);

	//I put it here for testing, will move it in a better place later.
	if (DestroyEnemy == true)
		SDL_DestroyTexture(this->enemytexture);





}

void Player::clean()
{
	SDL_DestroyTexture(this->playertexture);
	SDL_DestroyTexture(this->enemytexture);
}