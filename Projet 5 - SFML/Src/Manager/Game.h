#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "States/StateMainMenu.h"
#include "States/StateLevel.h"
#include "States/StateCombat.h"
#include "States/StateGameover.h"

#include "Manager/Resource/ResourceManager.h"
#include "Manager/Resource/MusicManager.h"
#include "Manager/Resource/SoundManager.h"

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
	Map getMap();
	void setMap(Map);

	void saveData();
	void loadData();

	sf::RenderWindow& getWindow() { return window; }

	ResourceManager& getResourceManager() { return resourceManager; }
	MusicManager& getMusicManager() { return musicManager; }
	SoundManager& getSoundManager() { return soundManager; }

	void setCamera(sf::View camera) { window.setView(camera);}


	// Game instance.
public:  static Game& getInstance() { return *instance; }
private: static Game* instance;

	// Game states.
public:

	StateMainMenu* stateMainMenu;
	StateLevel*    stateLevel;
	StateCombat*   stateCombat;
	StateGameover* stateGameover;

	Map map;
	string mapName;
	sf::Vector2i posPlayer;
	bool isIntro;


private:

	sf::RenderWindow window;

	ResourceManager resourceManager;
	MusicManager musicManager;
	SoundManager soundManager;
};
