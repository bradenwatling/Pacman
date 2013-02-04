#include <windows.h>
#include "LevelReader.h"
#include "SDL.h"

const int FONT_SIZE = 24;

int main(int argc, char *argv[])
{
	SDL sdl;
	SDL_Event e;
	int startTime = 0;
	bool run = true;

	LevelReader lr("level.txt");
	sdl.initializeSDL();
	Level l = lr.createLevel(sdl);
	l.drawLevel();

	startTime = SDL_GetTicks();

	while(run)
	{
		if(l.getPacman()->getPoints() == Pacman::numDots + Pacman::numBigDots * 5)
		{
			MessageBox(NULL, "You win!", "Congratulations!", NULL);
			run = false;
			break;
		}
		while(SDL_PollEvent(&e))
		{
			l.getPacman()->handleEvents(e);
			if(e.type == SDL_QUIT)
			{
				run = false;
				break;
			}
		}
		l.getPacman()->move();
		l.getPacman()->show();
		SDL_Flip(sdl.getScreen());
	}
	return 0;
}