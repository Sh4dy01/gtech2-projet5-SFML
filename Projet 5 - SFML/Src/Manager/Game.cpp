#include "Game.h"
#include "Map/Map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;
static const char* const SAVEMAP_FILE = "Maps.txt";

sf::RenderWindow* Game::window;
int Game::width;
int Game::height;

StateMainMenu* Game::stateMainMenu;
StateLevel*    Game::stateLevel;
StateCombat*   Game::stateCombat;


void Game::Initialization()
{
	width = 1920;
	height = 1080;

	window = new sf::RenderWindow(sf::VideoMode(width, height), "Pokemon : Origins");
	window->setFramerateLimit(144);

	stateMainMenu = new StateMainMenu();
	stateLevel    = new StateLevel();
	stateCombat   = new StateCombat();

	State::setDefaultState(stateMainMenu);
}


void Game::MapLoader()
{
	ifstream f(SAVEMAP_FILE);
	bool mapLoading = false;
	bool tabLoading = false;
	int width = 0;
	int length = 0;
	int indexX = 0;
	int indexY = 0;

	// If settings file does not exist yet, return error.
	if (!f) {
		cout << "error : file Maps.txt does not exist." << endl;
		return;
	}

	string line, id;
	while (!f.eof())
	{
		// Get line.
		getline(f, line);

		// Ignore empty line.
		if (line.empty()) {
			continue;
		}

		// Formatted reading.
		stringstream ss(line);
		ss >> id;

		if (id == ">") {
			mapLoading = true;
		}

		if (mapLoading) {

			if (id == "length") {
				ss >> length;
			}
			else if (id == "width") {
				ss >> width;
			}



		}

		// create tab if length and width aren't empty.


		f.close();
	}
}
