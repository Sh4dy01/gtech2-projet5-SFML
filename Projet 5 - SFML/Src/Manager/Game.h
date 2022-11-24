#pragma once
#include <SFML/Graphics.hpp>

#include "States/StateMainMenu.h"
#include "States/StateLevel.h"
#include "States/StateCombat.h"

#include "Manager/Resource/ResourceManager.h"

class Game {

public:

	static void Initialization();
	static void MapLoader();

public:

	static sf::RenderWindow* getWindow() { return window; }

	static ResourceManager* getResourceManager() { return resourceManager; }

	static int GetWidth() { return width; }
	static int GetHeight() { return height; }

public:

	static StateMainMenu* stateMainMenu;
	static StateLevel*    stateLevel;
	static StateCombat*   stateCombat;

private:
	static sf::RenderWindow* window;

	static ResourceManager* resourceManager;

	static int width;
	static int height;
};