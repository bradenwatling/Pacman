#include "LevelReader.h"

int LevelReader::lineCount = 0;
int LevelReader::lineLength = -1;

LevelReader::LevelReader(string path)
{
	string line;
	lineCount = -1;
	lineLength = 0;
	stream.open(path.c_str(), ios::in);
	if(stream.is_open())
	{
		while(!stream.eof())
		{
			getline(stream, line);
			lines[++lineCount] = line;
			if(line.length() > (unsigned)lineLength)
			{
				lineLength = line.length();
			}
		}
		stream.close();
	}
}

Level LevelReader::createLevel(SDL sdl)
{
	Level level(lineCount, lines, sdl);
	return level;
}