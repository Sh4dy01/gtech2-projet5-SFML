#include "ResourceManager.h"

#include "Manager/SpriteConfig.h"


ResourceManager::ResourceManager()
{

}

sf::Texture& ResourceManager::loadImage(const char* filename)
{
	auto elem = images.find(filename);

	if (elem == images.end()) {
		std::string path = BASE_IMAGE_PATH;
		path += filename;

		sf::Texture tex;
		tex.loadFromFile(path);

		return images.insert(std::pair<std::string, sf::Texture&>(filename, tex)).first->second;
	}
	else {
		return elem->second;
	}
}

sf::Font& ResourceManager::loadFont(const char* filename)
{
	auto elem = fonts.find(filename);

	if (elem == fonts.end()) {
		std::string path = BASE_IMAGE_PATH;
		path += filename;

		sf::Font font;
		font.loadFromFile(path);

		return fonts.insert(std::pair<std::string, sf::Font&>(filename, font)).first->second;
	}
	else {
		return elem->second;
	}
}
