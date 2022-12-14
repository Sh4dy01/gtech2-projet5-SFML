#pragma once

#include <SFML/Graphics.hpp>

#include <map>
#include <string>
#include "Map/Map.h"
#include "Tiles/Tile.h"

class ResourceManager
{
public:

	ResourceManager();

	// changement de map
	sf::Vector2i eventModifyCurrentMap(int x, int y);

	void MapLoader(Map& outMap, const std::string& name);
	void EventLoader(Map& outMap);
	Tile* TileLoader(int index);
	int fileLoader(string fileName);
	bool getCollision(int index);

	sf::Texture& loadImage(const char* fileName);
	sf::Texture& loadSprite(const char* fileName, bool isPokemon);
	sf::Texture& loadTile(const char* fileName);

	sf::Font& loadFont(const char* filename);

	Tile getTile(int index);


private:

	std::map<std::string, sf::Texture> images;
	std::map<std::string, sf::Texture> sprites;
	std::map<std::string, sf::Font> fonts;

	std::vector<Tile> loadedTiles;
	std::vector<int> loadedTilesIndex;
	std::vector<sf::Texture*> loadedTextures;
	std::vector<string> loadedPng;
	std::vector<int> collision;

	/// manage envent ///
	// change map
	std::vector<std::string> eventCurrentMap;
	std::vector<std::string> eventNewCurrentMap;
	std::vector<sf::Vector2i> eventPosition;
	std::vector<sf::Vector2i> eventNewPosition;

	
};
