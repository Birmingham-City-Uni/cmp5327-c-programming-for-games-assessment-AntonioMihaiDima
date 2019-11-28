#pragma once
#include <SDL.h>
#include <SDL_image.h>







class Tilemap {
public:


	bool isMoving = false;

	Tilemap(SDL_Renderer*);

	void init();
	void processInput(SDL_Event e);
	void update();
	void draw();
	void clean();

	int tilearrayvalues[48]; //An array which stores a random number sequence for positioning
	int tilemaparraymodified[50][25]; //Use this array to switch the values based on the tiles scrolling
	int tilemaparray[50][25]; //Bidimentional array to store the map tiles

	

	int width = 32;
	int height = 32;
	bool WaveComplete = false;
	bool uppercollision = false;

private:

	SDL_Texture* MapTex;
	SDL_Texture* WallTex;
	SDL_Texture* WaterTex;
	SDL_Renderer * renderer;
	SDL_Rect * firstposition;
	SDL_Rect * secondposition;
	SDL_Rect * thirdposition;

	
protected:

	
};

