#include "Map.h"

void Map::setLength(int length)
{
	this->length = length;
}

void Map::setWidth(int width)
{
	this->width = width;
}

void Map::setMap(Tile* tab)
{
	this->tab = tab;
}

void Map::setName(const char* name)
{
	this->name = name;
}

void Map::setValue(Tile* value, int x, int y)
{
	tab == value;
}

int Map::getLength()
{
	return this->length;
}

int Map::getWidth()
{
	return this->width;
}

Tile* Map::getMap()
{
	return this->tab;
}

const char* Map::getName()
{
	return this->name;
}

