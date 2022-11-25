#pragma once
#include <iostream>

class Tile;

class Map
{
public:
	Map();

	void         setLength(int length);
	void         setWidth(int width);
	void         setName(std::string name);
	void         setValue(int value, int x, int y);
		
	int          getLength();
	int          getWidth();
	int			 getValue(int x, int y);
	std::string  getName();

private:

	std::string name;

	// dimensions of the map
	int length;
	int width;

	// Tab of pointer of Tile
	int tab[64][64];
};
