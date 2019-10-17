#include "Player.h"

Player::Player(SDL_Renderer * renderer)
{
	this->renderer = renderer;
}


void Player::Init()
{
	SDL_Surface * surface = IMG_Load("Dirt.bmp");
	this->texture = SDL_CreateTextureFromSurface(this->renderer, surface);
	SDL_FreeSurface(surface);
}


void Player::processInput(SDL_Event e)
{

}

void Player::Update()
{

}
