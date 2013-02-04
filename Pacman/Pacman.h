#pragma once
#include "SDL.h"

enum
{
	PACMAN_RIGHT = 0,
	PACMAN_LEFT = 1,
	PACMAN_DOWN = 2,
	PACMAN_UP = 3,
	PACMAN_SIZE = 16
};

class Level;

class Pacman
{
public:
	Pacman(int X, int Y, SDL_Surface* Screen, string path);
	
	static SDL_Rect* walls;
	static SDL_Rect* dots;
	static SDL_Rect* bigDots;
	static SDL_Rect* teleporters;
	static int numWalls;
	static int numDots;
	static int numBigDots;
	static int numTeleporters;

	static void updateWalls(SDL_Rect* Walls, int numwalls);
	static void updateDots(SDL_Rect* Dots, int numdots);
	static void updateBigDots(SDL_Rect* BigDots, int numbigdots);
	static void updateTeleporters(SDL_Rect* Teleporters, int numteleporters);

	int getPoints();
	SDL_Surface* getScreen();
	void cacheScreen();
	void loadImage(string path);
	void handleEvents(SDL_Event ev);
	void move();
	void show();
	void drawImage(SDL_Rect clip);
	void collision(bool& right, bool& left, bool& down, bool& up);
	void setClips();

private:
	SDL_Surface* screen;
	SDL_Surface* screenCache;
	SDL_Surface* pacman;
	SDL_Rect clips[4][3];
	SDL_Rect pos;
	int xSpeed;
	int ySpeed;
	int frame;
	int status;
	int points;
	int teleporterTime;
};