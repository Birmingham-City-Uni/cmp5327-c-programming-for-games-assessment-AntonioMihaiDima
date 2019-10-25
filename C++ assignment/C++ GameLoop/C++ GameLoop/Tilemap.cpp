#include "Tilemap.h"
#include "pch.h"
using namespace std;

int TypeOfTerrain = 0;


Tilemap::Tilemap(SDL_Renderer * renderer)
{
	this -> renderer = renderer;
}




void Tilemap::init()
{
		SDL_Surface* tmpSurface = IMG_Load("debug/Dirt.jpg");
		SDL_Surface* brickSurface = IMG_Load("debug/Brick.jpg");
		MapTex = SDL_CreateTextureFromSurface(this->renderer, tmpSurface);
		WallTex = SDL_CreateTextureFromSurface(this->renderer, brickSurface);
		SDL_FreeSurface(tmpSurface);
		SDL_FreeSurface(brickSurface);

		position.x = 0;
		position.y = 0;
		position.h = 32;
		position.w = 32;
	

}


void Tilemap::processInput(SDL_Event e)
{

}


void Tilemap::update()
{

}


void Tilemap::draw()
{
	for (int i = 0; i < 25; i++) 
		for (int j = 0; j < 19; j++)
		{
			SDL_Rect position = { i * 32, j * 32, 32, 32 };
			SDL_RenderCopy(this->renderer, MapTex, NULL, &position);
		}
	for (int i = 0; i < 2; i++)
	for (int j = 0; j < 19; j++)
	{
		SDL_Rect position = { i * 768, j * 32, 32, 32 };
		SDL_RenderCopy(this->renderer, WallTex, NULL, &position);
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
