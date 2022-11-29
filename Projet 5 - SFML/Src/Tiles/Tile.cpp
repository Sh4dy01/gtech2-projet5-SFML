#include "Tile.h"

Tile::Tile()
{
	this->f = "";
	this->posX = 0;
	this->posY = 0;
	this->index = 0;
	this->collision = false;

}


// setters
void Tile::setPosX(int x)
{
	this->posX = x;
}

void Tile::setPosY(int y)
{
	this->posY = y;
}

void Tile::setIndex(int index)
{
	this->index = index;
}

void Tile::setFile(const string f)
{
	this->f = f;
}


// getters
int Tile::getPosX()
{
	return this->posX;
}

int Tile::getPosy()
{
	return this->posY;
}

int Tile::getIndex()
{
	return this->index;
}

const string Tile::getFile()
{
	return this->f;
}
