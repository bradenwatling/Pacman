#include "Level.h"

enum 
{
	doubleTopLeft = '~',
	doubleTopRight = '`',
	doubleBottomLeft = '1',
	doubleBottomRight = '!',
	singleTopLeft = '2',
	singleTopRight = '@',
	singleBottomLeft = '4',
	singleBottomRight = '$',
	squareTopLeft = '5',
	squareTopRight = '%',
	squareBottomLeft = '6',
	squareBottomRight = '^',
	doubleHorizontal = '=',
	singleHorizontal = '-',
	doubleVertical = '#',
	singleVertical = '|',
	dot = '.',
	bigDot = 'o',
	empty = ' ',
	teleporter = 't',
	casePacman = '0'
};

char lastChar;

Level::Level(int numLines, std::map<int,string> fileText, SDL Sdl)
{
	text = fileText;
	sdl = Sdl;
	lineCount = numLines;
	lineLength = LevelReader::lineLength;
	wallNum = 0;
	dotNum = 0;
	bigDotNum = 0;
	teleporterNum = 0;
	message = NULL;
}

void Level::addToWalls(int x, int y)
{
	if(wallNum < sizeof(walls))
	{
		walls[wallNum].x = x;
		walls[wallNum].y = y;
		walls[wallNum].w = PACMAN_SIZE;
		walls[wallNum].h = PACMAN_SIZE;
		wallNum++;
	}
}

void Level::addToDots(int x, int y)
{
	if(dotNum < sizeof(dots))
	{
		dots[dotNum].x = x;
		dots[dotNum].y = y;
		dots[dotNum].w = PACMAN_SIZE;
		dots[dotNum].h = PACMAN_SIZE;
		dotNum++;
	}
}

void Level::addToBigDots(int x, int y)
{
	if(bigDotNum < sizeof(bigDots))
	{
		bigDots[bigDotNum].x = x;
		bigDots[bigDotNum].y = y;
		bigDots[bigDotNum].w = PACMAN_SIZE;
		bigDots[bigDotNum].h = PACMAN_SIZE;
		bigDotNum++;
	}
}
void Level::addToTeleporters(int x, int y)
{
	if(teleporterNum < sizeof(bigDots))
	{
		teleporters[teleporterNum].x = x;
		teleporters[teleporterNum].y = y;
		teleporters[teleporterNum].w = PACMAN_SIZE;
		teleporters[teleporterNum].h = PACMAN_SIZE;
		teleporterNum++;
	}
}

int Level::getWallNum()
{
	return wallNum;
}

int Level::getDotNum()
{	
	return dotNum;
}

int Level::getBigDotNum()
{
	return bigDotNum;
}

int Level::getTeleporterNum()
{
	return bigDotNum;
}

void Level::drawLevel()
{
	string line;
	map<int, string>::iterator iter;
	for(int y = 0; y <= lineCount; ++y)
	{
		iter = text.find(y);
		line = iter->second;
		handleLine(line, y);
	}
	pacman->cacheScreen();
	pacman->move();
	pacman->show();
}

void Level::handleLine(string line, int y)
{
	int X = 0;
	int Y = y * PACMAN_SIZE;
	for(unsigned int x = 0; x < line.length(); ++x)
	{
		X = x * PACMAN_SIZE;
		switch(line[x])
		{
			case doubleTopLeft:
				sdl.loadBMP("GFX\\double_top_left_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case doubleTopRight:
				sdl.loadBMP("GFX\\double_top_right_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case doubleBottomLeft:
				sdl.loadBMP("GFX\\double_bottom_left_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case doubleBottomRight:
				sdl.loadBMP("GFX\\double_bottom_right_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case singleTopLeft:
				sdl.loadBMP("GFX\\single_top_left_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case singleTopRight:
				sdl.loadBMP("GFX\\single_top_right_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case singleBottomLeft:
				sdl.loadBMP("GFX\\single_bottom_left_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case singleBottomRight:
				sdl.loadBMP("GFX\\single_bottom_right_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case squareTopLeft:
				sdl.loadBMP("GFX\\square_top_left_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case squareTopRight:
				sdl.loadBMP("GFX\\square_top_right_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case squareBottomLeft:
				sdl.loadBMP("GFX\\square_bottom_left_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case squareBottomRight:
				sdl.loadBMP("GFX\\square_bottom_right_corner.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case doubleHorizontal:
				sdl.loadBMP("GFX\\double_line_horizontal.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case singleHorizontal:
				sdl.loadBMP("GFX\\single_line_horizontal.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case doubleVertical:
				sdl.loadBMP("GFX\\double_line_vertical.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case singleVertical:
				sdl.loadBMP("GFX\\single_line_vertical.bmp", X, Y);
				addToWalls(X, Y);
				break;
			case dot:
				sdl.loadBMP("GFX\\dot.bmp", X, Y);
				addToDots(X, Y);
				break;
			case bigDot:
				sdl.loadBMP("GFX\\big_dot.bmp", X, Y);
				addToBigDots(X, Y);
				break;
			case empty:
				sdl.loadBMP("GFX\\empty.bmp", X, Y);
				break;
			case teleporter:
				addToTeleporters(X, Y);
				break;
		}
		if(lastChar == casePacman && line[x] == casePacman)
		{
			sdl.loadBMP("GFX\\empty.bmp", X - PACMAN_SIZE, Y);

			pacman = new Pacman(X, Y, sdl.getScreen(), "GFX\\pac_man.bmp");
		}
		lastChar = line[x];
	}
	Pacman::updateWalls(walls, wallNum);
	Pacman::updateDots(dots, dotNum);
	Pacman::updateBigDots(bigDots, bigDotNum);
	Pacman::updateTeleporters(teleporters, teleporterNum);
}

Pacman* Level::getPacman()
{
	return pacman;
}

SDL_Rect* Level::getWalls()
{
	return walls;
}