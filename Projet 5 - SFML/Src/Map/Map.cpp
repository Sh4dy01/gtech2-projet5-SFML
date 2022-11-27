#include "Map.h"
#include "Tiles/Tile.h"
#include "Manager/Game.h"
#include "Manager/SpriteConfig.h"

Map::Map()
{
	for (int i = 0; i < 64; i++) {
		for (int j = 0; j < 64; j++) {
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

void Map::render()
{
	Tile temptile;
	for (int i = 0; i < this->width; i++) {
		for (int j = 0; j < this->length; j++) {
			temptile = Game::getInstance().getResourceManager().TileLoader( this->tab[i][j]);
			temptile.setPosition(i * SPRITE_SIZE,j * SPRITE_SIZE);
			Game::getInstance().getWindow().draw(temptile);
		}
	}

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

