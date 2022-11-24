#include "Map.h"

Map::Map()
{
	for (int i = 0; i < 100; i++) {
		for (int j = 0; j < 100; j++) {
			this->tab[i][j] = 0;
		}
	}
}

void Map::setLength(int length)
{
	this->length = length;
}

void Map::setWidth(int width)
{
	this->width = width;
}

void Map::setName(std::string name)
{
	this->name = name;
}

void Map::setValue(int value, int x, int y)
{
	tab[x][y] = value;
}

int Map::getLength()
{
	return this->length;
}

int Map::getWidth()
{
	return this->width;
}

int Map::getValue(int x, int y)
{
	return this->tab[x][y];
}

std::string Map::getName()
{
	return this->name;
}

