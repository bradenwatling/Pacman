#include "Level.h"
#include "Pacman.h"

SDL_Rect* Pacman::walls = new SDL_Rect();
SDL_Rect* Pacman::dots = new SDL_Rect();
SDL_Rect* Pacman::bigDots = new SDL_Rect();
SDL_Rect* Pacman::teleporters = new SDL_Rect();
int Pacman::numWalls = 0;
int Pacman::numDots = 0;
int Pacman::numBigDots = 0;
int Pacman::numTeleporters = 0;

Pacman::Pacman(int X, int Y, SDL_Surface* Screen, string path)
{
	screen = Screen;
	setClips();
    pos.x = X;
	pos.y = Y;
	pos.w = PACMAN_SIZE;
	pos.h = PACMAN_SIZE;
    xSpeed = 0;
	ySpeed = 0;
    frame = 0;
    status = PACMAN_RIGHT;
	points = 0;
	loadImage(path);
	teleporterTime = 0;
}

void Pacman::updateWalls(SDL_Rect* Walls, int numwalls)
{
	walls = Walls;
	numWalls = numwalls;
}

void Pacman::updateDots(SDL_Rect* Dots, int numdots)
{
	dots = Dots;
	numDots = numdots;
}

void Pacman::updateBigDots(SDL_Rect* BigDots, int numbigdots)
{
	bigDots = BigDots;
	numBigDots = numbigdots;
}

void Pacman::updateTeleporters(SDL_Rect* Teleporters, int numteleporters)
{
	teleporters = Teleporters;
	numTeleporters = numteleporters;
}

int Pacman::getPoints()
{
	return points;
}

SDL_Surface* Pacman::getScreen()
{
	return screen;
}

void Pacman::cacheScreen()
{
	screenCache = SDL_DisplayFormat(screen);
}

void Pacman::loadImage(string path)
{
	SDL_Surface* loadedImage = NULL;
    SDL_Surface* optimizedImage = NULL;
    loadedImage = SDL_LoadBMP(path.c_str());
    if(loadedImage)
	{
        optimizedImage = SDL_DisplayFormat(loadedImage);
        SDL_FreeSurface(loadedImage);
        if(optimizedImage)
        {
            SDL_SetColorKey(optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0, 0));
			pacman = optimizedImage;
        }
    }
}

void Pacman::handleEvents(SDL_Event ev)
{
	if(ev.type == SDL_KEYDOWN)
	{
		switch(ev.key.keysym.sym)
		{
			case SDLK_RIGHT:
				xSpeed = PACMAN_SIZE;
				break;
			case SDLK_LEFT:
				xSpeed = -PACMAN_SIZE;
				break;
			case SDLK_DOWN:
				ySpeed = PACMAN_SIZE;
				break;
			case SDLK_UP:
				ySpeed = -PACMAN_SIZE;
				break;
		}
	}
	else if(ev.type == SDL_KEYUP)
	{
		switch(ev.key.keysym.sym)
		{
			case SDLK_RIGHT:
				xSpeed = 0;
				break;
			case SDLK_LEFT:
				xSpeed = 0;
				break;
			case SDLK_DOWN:
				ySpeed = 0;
				break;
			case SDLK_UP:
				ySpeed = 0;
				break;
		}
	}
}

void Pacman::move()
{
	bool right = false, left = false, down = false, up = false;
	collision(right, left, down, up);
	if(xSpeed != 0)
	{
		if(xSpeed > 0 && !right)
		{
			pos.x += xSpeed;
		}
		if(xSpeed < 0 && !left)
		{
			pos.x += xSpeed;
		}
	}
	else if(ySpeed != 0)
	{
		if(ySpeed > 0 && !down)
		{
			pos.y += ySpeed;
		}
		if(ySpeed < 0 && !up)
		{
			pos.y += ySpeed;
		}
	}

	if((pos.x < 0 ) || (pos.x + PACMAN_SIZE > SDL::SCREEN_WIDTH - SDL::EXTRA_WIDTH))
    {
        pos.x -= xSpeed;
    }
	if((pos.y < 0 ) || (pos.y + PACMAN_SIZE > SDL::SCREEN_HEIGHT))
    {
        pos.y -= ySpeed;
    }
}

void Pacman::show()
{
	if(xSpeed < 0)
	{
		status = PACMAN_LEFT;
		frame++;
	}
	else if(xSpeed > 0)
	{
		status = PACMAN_RIGHT;
		frame++;
	}
	else if(ySpeed < 0)
	{
		status = PACMAN_UP;
		frame++;
	}
	else if(ySpeed > 0)
	{
		status = PACMAN_DOWN;
		frame++;
	}
	else
	{
		frame = 0;
	}

    if(frame >= 3)
    {
        frame = 0;
    }
	drawImage(clips[status][frame]);
	SDL_Delay(70);
}

void Pacman::drawImage(SDL_Rect clip)
{
	SDL_BlitSurface(screenCache, NULL, screen, NULL);
	SDL_BlitSurface(pacman, &clip, screen, &pos);
	SDL_Flip(screen);
}

void Pacman::collision(bool& right, bool& left, bool& down, bool& up)
{
	right = false;
	left = false;
	down = false;
	up = false;
	SDL_Rect temp;
	for(int i = 0; i <= numWalls; ++i)
	{
		temp = walls[i];
		if(temp.x == (pos.x - PACMAN_SIZE) && temp.y == pos.y)
		{
			left = true;
			continue;
		}
		else if(temp.x == (pos.x + PACMAN_SIZE) && temp.y == pos.y)
		{
			right = true;
			continue;
		}
		else if(temp.y == (pos.y - PACMAN_SIZE) && temp.x == pos.x)
		{
			up = true;
			continue;
		}
		else if(temp.y == (pos.y + PACMAN_SIZE) && temp.x == pos.x)
		{
			down = true;
			continue;
		}
	}
	
	for(int i = 0; i <= numDots; ++i)
	{
		temp = dots[i];
		if(temp.x == pos.x && temp.y == pos.y)
		{
			SDL_FillRect(screenCache, &temp, SDL_MapRGB(screen->format, 0, 0, 0));
			points ++;
			dots[i] = SDL_Rect();
			break;
		}
	}


	for(int i = 0; i <= numBigDots; ++i)
	{
		temp = bigDots[i];
		if(temp.x == pos.x && temp.y == pos.y)
		{
			SDL_FillRect(screenCache, &temp, SDL_MapRGB(screen->format, 0, 0, 0));
			points += 5;
			bigDots[i] = SDL_Rect();
			break;
		}
	}

	for(int i = 0; i <= numTeleporters; ++i)
	{
		temp = teleporters[i];
		if(temp.x == pos.x && temp.y == pos.y)
		{
			if(i == 0 && SDL_GetTicks() - teleporterTime >= 500)
			{
				pos.x = teleporters[1].x;
				pos.y = teleporters[1].y;
				teleporterTime = SDL_GetTicks();
			}
			else if (i == 1 && SDL_GetTicks() - teleporterTime >= 500)
			{
				pos.x = teleporters[0].x;
				pos.y = teleporters[0].y;
				teleporterTime = SDL_GetTicks();
			}
			break;
		}
	}
}

void Pacman::setClips()
{
	for(int i = 0; i < 4; ++i)
	{
		for(int x = 0; x < 3; ++x)
		{
			clips[i][x].x = PACMAN_SIZE * x;
			clips[i][x].y = PACMAN_SIZE * i;
			clips[i][x].w = PACMAN_SIZE;
			clips[i][x].h = PACMAN_SIZE;
		}
	}
}