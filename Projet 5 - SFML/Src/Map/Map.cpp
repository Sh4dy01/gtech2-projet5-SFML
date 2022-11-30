#include "Map.h"
#include "Tiles/Tile.h"
#include "Manager/Game.h"
#include "Manager/SpriteConfig.h"
#include "Manager/AnimatedEntity.h"

Map::Map()
{
	int nbrEntity = 0;
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
		for (int y = 0; y < this->length; y++) {
			temptile = *Game::getInstance().getResourceManager().TileLoader( this->tab[y][i] );
			temptile.setPosition( i * SPRITE_SIZE + 8, y * SPRITE_SIZE + 8);
			Game::getInstance().getWindow().draw(temptile);
		}
	}
}

bool Map::thereIsCollision(int x, int y, int dir)
{
	cout << x << " : " << y << " = " << this->tab[y][x] << endl;
	for (int i = 0; i < this->length; i++) {
		for (int j = 0; j < this->width; j++) {
			cout << this->tab[i][j] << " ";
		}
		cout << endl;
	}
	switch (dir)
	{
	case UP:
		if (y - 1 < 0) {
			return true;
		}
		else {
			return Game::getInstance().getResourceManager().getCollision(this->tab[y - 1][x]);
		}
		break;

	case DOWN:
		if (y + 1 >= this->length) {
			return true;
		}
		else {
			return Game::getInstance().getResourceManager().getCollision(this->tab[y + 1][x]);
		}
		break;

	case RIGHT:
		if (x + 1 >= this->width) {
			return true;
		}
		else {
			return Game::getInstance().getResourceManager().getCollision(this->tab[y][x + 1]);
		}
		break;

	case LEFT:
		if (x - 1 < 0) {
			return true;
		}
		else {
			return Game::getInstance().getResourceManager().getCollision(this->tab[y][x - 1]);
		}
		break;

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

std::string& Map::getName()
{
	return this->name;
}

void Map::setPosX(std::vector<int>& posX)
{
	this->posX = posX;
}

void Map::setPosY(std::vector<int>& posY)
{
	this->posY = posY;
}

void Map::setDir(std::vector<int>& dir)
{
	this->dir = dir;
}

void Map::setEntityName(std::vector<std::string>& entityName)
{
	this->entityName = entityName;
}

void Map::setType(std::vector<std::string>& type)
{
	this->type = type;
}

void Map::setNbrEntity(int nbrEntity)
{
	this->nbrEntity = nbrEntity;
}

int Map::getNbrEntity()
{
	return nbrEntity;
}

std::vector<int>& Map::getPosX()
{
	return this->posX;
}

std::vector<int>& Map::getPosY()
{
	return this->posY;
}

std::vector<int>& Map::getDir()
{
	return this->dir;
}

std::vector<std::string>& Map::getEntityName()
{
	return this->entityName;
}

std::vector<std::string>& Map::getType()
{
	return this->type;
}