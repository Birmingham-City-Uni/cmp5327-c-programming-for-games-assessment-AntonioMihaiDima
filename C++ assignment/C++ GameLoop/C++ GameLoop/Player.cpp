#include "Player.h"
#include "GameLoop.h"

extern GameLoop * gameLoop;



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

}

void Player::update()
{
	if (gameLoop->getKeyDown(SDL_SCANCODE_W))
	{
		xpos -= 2;
		angle = 0;
	}
	if (gameLoop->getKeyDown(SDL_SCANCODE_S))
	{
		xpos += 2;
		angle = 180;
	}
	if (gameLoop->getKeyDown(SDL_SCANCODE_A))
	{
		ypos -= 2;
		angle = 270;
	}
	if (gameLoop->getKeyDown(SDL_SCANCODE_D))
	{
		ypos += 2;
		angle = 90;
	}
	if ((gameLoop->getKeyDown(SDL_SCANCODE_W)) && (gameLoop->getKeyDown(SDL_SCANCODE_A)))
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