#include "SDL.h"
#include "LevelReader.h"

int SDL::SCREEN_WIDTH = 0;
int SDL::SCREEN_HEIGHT = 0;
int SDL::EXTRA_WIDTH = 0;

void SDL::initializeSDL()
{
	SCREEN_WIDTH = LevelReader::lineLength * PACMAN_SIZE + EXTRA_WIDTH;
	SCREEN_HEIGHT = LevelReader::lineCount * PACMAN_SIZE;
	if(!SDL_Init(SDL_INIT_AUDIO|SDL_INIT_VIDEO))
	{
        SDL_Quit();
    }
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 0, SDL_SWSURFACE);
	SDL_WM_SetCaption("Pacman", NULL);
    if(!screen)
	{
        SDL_Quit();
    }
}

void SDL::loadBMP(string file, int x, int y)
{	
	SDL_Surface* image;
    SDL_Rect dest;

    image = SDL_LoadBMP(file.c_str());
    if(image)
	{
		SDL_SetColorKey(image, SDL_SRCCOLORKEY, SDL_MapRGB(image->format, 0, 0, 0));
	
		dest.x = x;
		dest.y = y;
		dest.w = image->w;
		dest.h = image->h;

		SDL_BlitSurface(image, NULL, screen, &dest);
		SDL_UpdateRects(screen, 1, &dest);
	}
}

SDL_Surface* SDL::getScreen()
{
	return screen;
}