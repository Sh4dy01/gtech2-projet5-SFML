#pragma once
#include <SFML/Graphics.hpp>

#include "States/StateMainMenu.h"
#include "States/StateLevel.h"
#include "States/StateCombat.h"
#include "States/StateSettingsMenu.h"

#include "Manager/Resource/ResourceManager.h"


// Render space is the same as a Gameboy console's.
// Window resize will cause the rendered frame to stretch.
#define GAME_SIZE_X 256
#define GAME_SIZE_Y 256

class Map;
class Tile;

class Game
{
public:

	Game();

	void Initialization();

public:

	sf::RenderWindow& getWindow() { return window; }

	ResourceManager& getResourceManager() { return resourceManager; }



	// Game instance.
public:  static Game& getInstance() { return *instance; }
private: static Game* instance;

	// Game states.
public:

	StateMainMenu* stateMainMenu;
	StateLevel*    stateLevel;
	StateCombat*   stateCombat;
	StateSettingsMenu* stateSettingsMenu;

private:

	sf::RenderWindow window;

	ResourceManager resourceManager;
};
