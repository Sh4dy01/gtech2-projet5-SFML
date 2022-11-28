#pragma once
#include <SFML/Graphics.hpp>

#include "States/StateMainMenu.h"
#include "States/StateLevel.h"
#include "States/StateCombat.h"

#include "Manager/Resource/ResourceManager.h"
#include "Manager/Audio/MusicManager.h"
#include "Manager/Audio/SoundManager.h"


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
	void QuitGame();

public:

	sf::RenderWindow& getWindow() { return window; }

	ResourceManager& getResourceManager() { return resourceManager; }
	MusicManager& getMusicManager() { return musicManager; }
	SoundManager& getSoundManager() { return soundManager; }



	// Game instance.
public:  static Game& getInstance() { return *instance; }
private: static Game* instance;

	// Game states.
public:

	StateMainMenu* stateMainMenu;
	StateLevel*    stateLevel;
	StateCombat*   stateCombat;

private:

	sf::RenderWindow window;

	ResourceManager resourceManager;
	MusicManager musicManager;
	SoundManager soundManager;
};
