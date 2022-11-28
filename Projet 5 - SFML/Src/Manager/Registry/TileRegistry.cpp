#include "TileRegistry.h"

std::vector<Tile> TileRegistry::tiles;


void TileRegistry::init()
{
	//registerTile(Tile("air", 0, false));
}

void TileRegistry::registerTile(const Tile& t)
{
	tiles.push_back(t);
	tiles.back().id = tiles.size() - 1;
}

Tile* TileRegistry::getTile(int id)
{
	return &tiles[id];
}
