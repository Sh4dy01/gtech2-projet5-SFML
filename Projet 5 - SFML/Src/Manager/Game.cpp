#include "Game.h"
#include "Map/Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


using namespace std;
static const char* const SAVEMAP_FILE = "Src/Manager/Maps.txt";

Game* Game::instance = 0;


Game::Game()
	: stateMainMenu(0), stateLevel(0), stateCombat(0)
{
	if (!instance) {
		instance = this;
	}
}

void Game::Initialization()
{
	window.create(sf::VideoMode(1024, 1024), "Pokemon : Origins");
	window.setVerticalSyncEnabled(true);

	sf::View view(sf::Vector2f(GAME_SIZE_X / 2, GAME_SIZE_Y / 2), sf::Vector2f(GAME_SIZE_X, GAME_SIZE_Y));
	window.setView(view);

	stateMainMenu = new StateMainMenu();
	stateLevel    = new StateLevel();
	stateCombat   = new StateCombat();

	State::setDefaultState(stateMainMenu);
}


Map* Game::MapLoader(std::string name)
{
	ifstream f(SAVEMAP_FILE);
	bool mapLoading = false;
	bool tabLoading = false;
	int width = 0;
	int length = 0;
	int countLine = 0;
	int countChar = 0;
	Map map;

	// If settings file does not exist yet, return error.
	if (!f) {
		cout << "error : file Maps.txt does not exist." << endl;
		return 0;
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
			countLine = -3;
		}

		if (id == "<") {
			mapLoading = false;
		}

		if (mapLoading) {

			if (id == "length") {
				ss >> length;
				map.setLength(length);
			}
			else if (id == "width") {
				ss >> width;
				map.setWidth(width);
			}
			else if (length != 0 && width != 0) {
				int id;
				for (int i = 0; i < width; i++) {
					ss >> id;
						map.setValue(id, countLine, countChar);
						countChar += 1;
				}
			}
		}

		// create tab if length and width aren't empty.

		countLine += 1;
		
	}
	f.close();
	return &map;
}
