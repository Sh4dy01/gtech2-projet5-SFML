#include "ResourceManager.h"
#include "Manager/SpriteConfig.h"
#include "Map/Map.h"
#include "Tiles/Tile.h"
#include "Manager/Game.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

#define EXTERIOR_FILE "exterior.png"
#define EXTERIOR_WIDTH 16
#define EXTERIOR_HEIGHT 7

#define INTERIOR_FILE "interior.png"
#define INTERIOR_WIDTH 13
#define INTERIOR_HEIGHT 9


using namespace std;
static const char* const SAVEMAP_FILE = "Src/Manager/Save/Maps.txt";
static const char* const SAVETILE_FILE = "Src/Manager/Save/Tiles.txt";
static const char* const SAVEEVENT_FILE = "Src/Manager/Save/Events.txt";


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

sf::Texture& ResourceManager::loadSprite(const char* filename, bool isPokemon)
{
	auto elem = sprites.find(filename);

	if (elem == sprites.end()) {
		std::string path = BASE_SPRITE_PATH;
		if (isPokemon) path += "Pokemon/";
		path += filename;
		path += BASE_SPRITE_EXTENSION;

		sf::Texture tex;
		tex.loadFromFile(path);

		std::cout << filename << " loaded !" << std::endl;

		return sprites.insert(std::pair<std::string, sf::Texture&>(filename, tex)).first->second;
	}
	else {
		std::cout << filename << " already loaded !" << std::endl;

		return elem->second;
	}
}

sf::Texture& ResourceManager::loadTile(const char* filename)
{
	auto elem = sprites.find(filename);

	if (elem == sprites.end()) {
		std::string path = BASE_TILES_PATH;
		path += filename;

		sf::Texture tex;
		tex.loadFromFile(path);

		return sprites.insert(std::pair<std::string, sf::Texture&>(filename, tex)).first->second;
	}
	else {
		return elem->second;
	}
}

sf::Font& ResourceManager::loadFont(const char* filename)
{
	auto elem = fonts.find(filename);

	if (elem == fonts.end()) {
		std::string path = BASE_FONT_PATH;
		path += filename;

		sf::Font font;
		font.loadFromFile(path);

		return fonts.insert(std::pair<std::string, sf::Font&>(filename, font)).first->second;
	}
	else {
		return elem->second;
	}
}
Tile ResourceManager::getTile(int index)
{
	return loadedTiles[index];
}


void ResourceManager::MapLoader(Map& outMap, const std::string& name)
{
	ifstream f(SAVEMAP_FILE);
	bool mapLoading = false;
	bool tabLoading = false;
	int width = 0;
	int height = 0;
	int countLine = 0;
	int countChar = 0;
	int nbrEntity = 0;
	std::vector<int> posX;
	std::vector<int> posY;
	std::vector<direction> dir;
	std::vector<std::string> entityName;
	std::vector<std::string> type;

	// If settings file does not exist yet, return error.
	if (!f) {
		cout << "error : file Maps.txt does not exist." << endl;
	}

	string line, id;
	while (!f.eof())
	{
		// Get line.
		getline(f, line);
		int countChar = 0;

		// Ignore empty line.
		if (line.empty()) {
			continue;
		}

		// Formatted reading.
		stringstream ss(line);
		ss >> id;

		if (id == name) {
			mapLoading = true;
			outMap.setName(name);
			countLine = -3;
		}

		if (id == "<") {
			mapLoading = false;
		}

		if (mapLoading) {

			if (id == "height") {
				ss >> height;
				outMap.setHeight(height);
			}
			else if (id == "width") {
				ss >> width;
				outMap.setWidth(width);
			}
			else if (id == "-" && height != 0 && width != 0) {
				int id;
				for (int i = 0; i < width; i++) {
					ss >> id;
					outMap.setValue(id, countLine, i);
					countChar += 1;
				}
			}
			else if (id == "nbrEntity") {
				ss >> nbrEntity;
				outMap.setNbrEntity(nbrEntity);
			}
			else if (id == "posX") {
				int tempValue = 0;
				for (int i = 0; i < nbrEntity; i++) {
					ss >> tempValue;
					posX.push_back(tempValue);
				}
				outMap.setPosX(posX);
			}
			else if (id == "posY") {
				int tempValue = 0;
				for (int i = 0; i < nbrEntity; i++) {
					ss >> tempValue;
					posY.push_back(tempValue);
				}
				outMap.setPosY(posY);
			}
			else if (id == "dir") {
				int tempValue = STILL;
				for (int i = 0; i < nbrEntity; i++) {
					ss >> tempValue;
					dir.push_back((direction)tempValue);
				}
				outMap.setDir(dir);
			}
			else if (id == "entity") {
				std::string tempString = "";
				for (int i = 0; i < nbrEntity; i++) {
					ss >> tempString;
					entityName.push_back(tempString);
				}
				outMap.setEntityName(entityName);
			}
			else if (id == "type") {
				std::string tempString = "";
				for (int i = 0; i < nbrEntity; i++) {
					ss >> tempString;
					type.push_back(tempString);
				}
				outMap.setType(type);
			}
		}

		// create tab if length and width aren't empty.

		countLine += 1;

	}

	f.close();
	this->EventLoader(outMap);
}

void ResourceManager::EventLoader(Map& outMap)
{
	eventCurrentMap.clear();
	eventNewCurrentMap.clear();
	eventPosition.clear();
	eventNewPosition.clear();

	ifstream f(SAVEEVENT_FILE);
	int nbrEvent = 0;
	std::vector<int> posX;
	std::vector<int> posY;
	std::vector<int> newPosX;
	std::vector<int> newPosY;
	std::vector<int> indexList;


	// If settings file does not exist yet, return error.
	if (!f) {
		cout << "error : file Maps.txt does not exist." << endl;
	}

	string line, id;
	while (!f.eof())
	{
		// Get line.
		getline(f, line);
		int countChar = 0;

		// Ignore empty line.
		if (line.empty()) {
			continue;
		}

		// Formatted reading.
		stringstream ss(line);
		ss >> id;
		
		if (id == "nbrEvent") {
			ss >> nbrEvent;
		}

		if (id == "eventCurrentMap") {
			for (int i = 0; i < nbrEvent; i++) {
				ss >> id;
				if (id == outMap.getName()) {
					indexList.push_back(i);
					eventCurrentMap.push_back(id);
				}

				
			}
		}

		if (id == "eventNewCurrentMap") {
			for (int i = 0; i < nbrEvent; i++) {
				ss >> id;
				for (int y = 0; y < indexList.size(); y++)
	            {  
					if (indexList[y] == i) {
						eventNewCurrentMap.push_back(id);
					}
				}
			}
		}

		if (id == "posX") {
			int temp = 0;
			for (int i = 0; i < nbrEvent; i++) {
				ss >> temp;
				for (int y = 0; y < indexList.size(); y++)
				{
					if (indexList[y] == i) {
						posX.push_back(temp);
					}
				}
			}
		}

		if (id == "posY") {
			int temp = 0;
			for (int i = 0; i < nbrEvent; i++) {
				ss >> temp;
				for (int y = 0; y < indexList.size(); y++)
				{
					if (indexList[y] == i) {
						posY.push_back(temp);
					}
				}
			}
		}

		if (id == "newPosX") {
			int temp = 0;
			for (int i = 0; i < nbrEvent; i++) {
				ss >> temp;
				for (int y = 0; y < indexList.size(); y++)
				{
					if (indexList[y] == i) {
						newPosX.push_back(temp);
					}
				}
			}
		}

		if (id == "newPosY") {
			int temp = 0;
			for (int i = 0; i < nbrEvent; i++) {
				ss >> temp;
				for (int y = 0; y < indexList.size(); y++)
				{
					if (indexList[y] == i) {
						newPosY.push_back(temp);
					}
				}
			}
		}
	}
	for (int i = 0; i < indexList.size(); i++) {
		eventPosition.push_back(sf::Vector2i(posX[i], posY[i]));
		eventNewPosition.push_back(sf::Vector2i(newPosX[i], newPosY[i]));
	}

	f.close();
}

Tile* ResourceManager::TileLoader(int index)
{
	for (int i = 0; i < loadedTilesIndex.size(); i++) {
		if (loadedTilesIndex[i] == index) {
			return &loadedTiles[i];
		}
	}

	ifstream f(SAVETILE_FILE);
	bool isLoading = false;
	int posX = 0;
	int posY = 0;
	string file;
	Tile tile;

	// If settings file does not exist yet, return error.
	if (!f) {
		cout << "error : file Maps.txt does not exist." << endl;
	}

	string line, id;
	int indexDetector;
	while (!f.eof())
	{
		// Get line.
		getline(f, line);
		int countChar = 0;

		// Ignore empty line.
		if (line.empty()) {
			continue;
		}

		// Formatted reading.
		stringstream ss(line);
		if (isLoading) {
			ss >> id;
		}
		else {
			ss >> indexDetector;
		}

		if (indexDetector == index) {
			isLoading = true;
		}

		if (id == "<") {
			isLoading = false;
		}

		if (isLoading) {

			if (id == "posX") {
				ss >> posX;
				tile.setPosX(posX);
			}
			else if (id == "posY") {
				ss >> posY;
				tile.setPosY(posY);
			}
			else if (id == "file") {
				ss >> file;
				tile.setFile(file);
			}
			else if (id == "collision") {
				string collided;
				ss >> collided;
				if (collided == "true")
				collision.push_back(index);
			}
		}


	}
	f.close();

	

	for (int i = 0; i < loadedPng.size(); i++) {
		if (loadedPng[i] == file) {
			tile.setTexture(*loadedTextures[i]);
			tile.setTextureRect(sf::IntRect(posX, posY, SPRITE_SIZE, SPRITE_SIZE));
			loadedTiles.push_back(tile);
			loadedTilesIndex.push_back(index);
			return &tile;

		}
	}
	
	int i = this->fileLoader(file);
	tile.setTexture(*loadedTextures[i]);
	tile.setTextureRect(sf::IntRect(posX, posY, SPRITE_SIZE, SPRITE_SIZE));
	loadedTiles.push_back(tile);
	loadedTilesIndex.push_back(index);
	return &tile;
}

int ResourceManager::fileLoader(string fileName)
{
	if (fileName == EXTERIOR_FILE) {
		sf::Texture& texture = Game::getInstance().getResourceManager().loadTile(fileName.c_str());
		loadedTextures.push_back(&texture);
		loadedPng.push_back(fileName);
		return loadedPng.size() - 1;
	}

	if (fileName == INTERIOR_FILE) {
		sf::Texture& texture = Game::getInstance().getResourceManager().loadTile(fileName.c_str());
		loadedTextures.push_back(&texture);
		loadedPng.push_back(fileName);
		return loadedPng.size() - 1;
	}

}

bool ResourceManager::getCollision(int index)
{
	for (int i = 0; i < collision.size(); i++) {
		if (collision[i]==index)
			return true;
	}
	return false;
}

sf::Vector2i ResourceManager::eventModifyCurrentMap(int x, int y)
{
	for (int i = 0; i < eventCurrentMap.size(); i++) {
		if (x == eventPosition[i].x && y == eventPosition[i].y) {
			Map newMap;
			int x, y;
			x = eventNewPosition[i].x;
			y = eventNewPosition[i].y;
			Game::getInstance().getResourceManager().MapLoader(newMap , eventNewCurrentMap[i]);
			Game::getInstance().setMap(newMap);
			return sf::Vector2i(x, y);
		}
	}
	return sf::Vector2i(-1, -1);
}
