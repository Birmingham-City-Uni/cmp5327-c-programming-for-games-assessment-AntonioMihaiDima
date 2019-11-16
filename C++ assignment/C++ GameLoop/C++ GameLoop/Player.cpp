#include "Player.h"



bool upmovement = false;
bool downmovement = false;
bool leftmovement = false;
bool rightmovement = false;
bool upperleft = false;
bool upperright = false;
bool bottomleft = false;
bool bottomright = false;

Player::Player(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void Player::init()
{
	SDL_Surface * surface = IMG_Load("debug/PlayerTexture.png");
	this->playertexture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);


}

void Player::processInput(SDL_Event e)
{
	if (e.type == SDL_KEYDOWN)
	{
		if (e.key.keysym.sym == SDLK_w)
		{
			upmovement = true;
		}
		if (e.key.keysym.sym == SDLK_s)
		{
			downmovement = true;
		}
		if (e.key.keysym.sym == SDLK_a)
		{
			leftmovement = true;
		}
		if (e.key.keysym.sym == SDLK_d)
		{
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
	
	if (upmovement == true)
	{
		xpos -= 2;
		angle = 0;
	}
	if (downmovement == true)
	{
		xpos += 2;
		angle = 180;
	}
	if (leftmovement == true)
	{
		ypos -= 2;
		angle = 270;
	}
	if (rightmovement == true)
	{
		ypos += 2;
		angle = 90;
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


	/*if ((gameLoop->getKeyDown(SDL_SCANCODE_W)) && (gameLoop->getKeyDown(SDL_SCANCODE_A)))
	{
		angle = 315;
	}
	if ((gameLoop->getKeyDown(SDL_SCANCODE_W)) && (gameLoop->getKeyDown(SDL_SCANCODE_D)))
	{
		angle = 45;
	}
	if ((gameLoop->getKeyDown(SDL_SCANCODE_S)) && (gameLoop->getKeyDown(SDL_SCANCODE_A)))
	{
		angle = 225;
	}
	if ((gameLoop->getKeyDown(SDL_SCANCODE_S)) && (gameLoop->getKeyDown(SDL_SCANCODE_D)))
	{
		angle = 135;
	}
	*/

}

void Player::draw()
{

	SDL_Rect position = { ypos, xpos, 32, 32 };
	SDL_Point * center = NULL;

	SDL_RenderCopyEx(this->renderer, this->playertexture, 0, &position, angle, center, SDL_FLIP_NONE);


}

void Player::clean()
{
	SDL_DestroyTexture(this->playertexture);
}