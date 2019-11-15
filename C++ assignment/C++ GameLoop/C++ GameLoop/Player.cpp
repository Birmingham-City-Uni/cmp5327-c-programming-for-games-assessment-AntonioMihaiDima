#include "Player.h"

extern GameLoop * gameLoop;

int xpos = 768;
int ypos = 384;
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
	}
	if (gameLoop->getKeyDown(SDL_SCANCODE_S))
	{
		xpos += 2;
	}
	if (gameLoop->getKeyDown(SDL_SCANCODE_A))
	{
		ypos -= 2;
	}
	if (gameLoop->getKeyDown(SDL_SCANCODE_D))
	{
		ypos += 2;
	}
}

void Player::draw()
{

	SDL_Rect position = { ypos, xpos, 32, 32 };

	SDL_RenderCopy(this->renderer, this->playertexture, 0, &position);


}

void Player::clean()
{
	SDL_DestroyTexture(this->playertexture);
}