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

	Map* MapLoader(const std::string& name);
	Tile TileLoader(int index);

	sf::Texture& loadImage(const char* fileName);
	sf::Texture& loadSprite(const char* fileName);

	sf::Font& loadFont(const char* filename);


private:

	std::map<std::string, sf::Texture> images;
	std::map<std::string, sf::Texture> sprites;
	std::map<std::string, sf::Font> fonts;
};
