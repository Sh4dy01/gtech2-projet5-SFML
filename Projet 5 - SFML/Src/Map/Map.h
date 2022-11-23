#pragma once

class Tile;

class Map
{
public:
	Map();

	void         setLength(int length);
	void         setWidth(int width);
	void         setMap(Tile* tab);
	void         setName(const char* name);
	void         setValue(Tile* value, int x, int y);
		
	int          getLength();
	int          getWidth();
	Tile*        getMap();
	const char*  getName();

private:

	const char* name;

	// dimensions of the map
	int length;
	int width;

	// Tab of pointer of Tile
	Tile* tab;
};
