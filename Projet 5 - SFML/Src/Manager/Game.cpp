#include "Game.h"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include "Manager/SpriteConfig.h"
#include "Manager/SpriteConfig.h"

#include "Resource/ResourceManager.h"

using namespace std;
static const char* const SAVEDATA_FILE = "Src/Manager/Save/Data.txt";

Game* Game::instance = 0;


Game::Game()
	: stateMainMenu(0), stateLevel(0), stateCombat(0), mapName("bedRoom"), posPlayer(2,3)
{

	if (!instance) {
		instance = this;
	}
}

void Game::Initialization()
{
	this->loadData();
	window.create(sf::VideoMode(1024, 1024), "Pokemon : Origins", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	window.setView(sf::View(sf::Vector2f(GAME_SIZE_X / 2, GAME_SIZE_Y / 2), sf::Vector2f(GAME_SIZE_X, GAME_SIZE_Y)));

	Game::getInstance().getResourceManager().MapLoader(map, mapName);

	stateMainMenu = new StateMainMenu();
	stateLevel    = new StateLevel(posPlayer);
	stateCombat   = new StateCombat();
	stateGameover = new StateGameover();

	State::setDefaultState(stateLevel);
}

void Game::QuitGame()
{
	window.close();
}

Map Game::getMap()
{
	return this->map;
}

void Game::setMap(Map map)
{
	this->map = map;
}

void Game::saveData() {
    ofstream f(SAVEDATA_FILE);

    string file;
    int index = 0;

    // If settings file does not exist yet  return error.
    if (!f) {
        cout << "error : file Maps.txt does not exist." << endl;
    }
	sf::Vector2f vect = this->stateLevel->getPlayer().getPosition();

    f << "currentMap " << this->getMap().getName() << endl;
    f << "playerPos " << vect.x / SPRITE_SIZE << " " << vect.y / SPRITE_SIZE << endl;
    index += 1;
  


    f.close();
}

void Game::loadData()
{
	ifstream f(SAVEDATA_FILE);

	// If settings file does not exist yet, return error.
	if (!f) {
		cout << "error : file Maps.txt does not exist." << endl;
	}
	int x, y;
	x = posPlayer.x;
	y = posPlayer.y;
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

		if (id == "currentMap") {
			ss >> id;
			this->mapName = id;
		}
		else if (id == "playerPos") {
			ss >> x;
			ss >> y;
		}
	}
	posPlayer = sf::Vector2i(x, y);
	f.close();
}
