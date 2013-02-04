#pragma once
#include <string>
#include <map>
#include "SDL.h"
#include "Pacman.h"
#include "LevelReader.h"

using namespace std;

class Level
{
public:
	Level(int numLines, map<int, string> fileText, SDL Sdl);
	void addToWalls(int x, int y);
	void addToDots(int x, int y);
	void addToBigDots(int x, int y);
	void addToTeleporters(int x, int y);
	int getWallNum();
	int getDotNum();
	int getBigDotNum();
	int getTeleporterNum();
	void drawLevel();
	void handleLine(string Char, int y);
	Pacman* getPacman();
	SDL_Rect* getWalls();

private:
	Pacman* pacman;
	map<int, string> text;
	SDL sdl;
	SDL_Surface* message;
	SDL_Rect walls[1000];
	SDL_Rect dots[1000];
	SDL_Rect bigDots[1000];
	SDL_Rect teleporters[2];
	int wallNum;
	int dotNum;
	int bigDotNum;
	int teleporterNum;
	int lineCount;
	int lineLength;
};