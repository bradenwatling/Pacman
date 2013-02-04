#pragma once
#include <string>
#include <SDL.h>

using namespace std;

class SDL
{
public:
	void initializeSDL();
	void loadBMP(string file, int x, int y);
	SDL_Surface* getScreen();
	static int SCREEN_WIDTH;
	static int SCREEN_HEIGHT;
	static int EXTRA_WIDTH;

private:
	SDL_Surface* screen;
};