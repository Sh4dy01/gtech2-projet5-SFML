#pragma once

#include <vector>

#include "Manager/Tile/Tile.h"


class TileRegistry
{
public:

	static void init();

	static void registerTile( const Tile& t );

	static Tile* getTile(int id);

private:

	static std::vector<Tile> tiles;
};
