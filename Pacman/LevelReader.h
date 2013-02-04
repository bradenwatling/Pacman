#pragma once
#include <string>
#include <fstream>
#include <map>
#include "Level.h"

using namespace std;

class LevelReader
{
public:
	LevelReader(string path);
	Level createLevel(SDL sdl);

	static int lineCount;
	static int lineLength;

private:
	ifstream stream;
	map<int, string> lines;
};