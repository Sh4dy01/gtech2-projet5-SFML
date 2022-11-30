#include "Game.h"
#include <iostream>
#include <algorithm>
#include "Manager/SpriteConfig.h"

#include "Resource/ResourceManager.h"


Game* Game::instance = 0;


Game::Game()
	: stateMainMenu(0), stateLevel(0), stateCombat(0), test(*Game::getInstance().getResourceManager().MapLoader("city")), test2(*Game::getInstance().getResourceManager().MapLoader("test2")), currentMap(&test)
{
	if (!instance) {
		instance = this;
	}
}

void Game::Initialization()
{
	window.create(sf::VideoMode(1024, 1024), "Pokemon : Origins", sf::Style::Titlebar | sf::Style::Close);
	window.setVerticalSyncEnabled(true);

	window.setView(sf::View(sf::Vector2f(GAME_SIZE_X / 2, GAME_SIZE_Y / 2), sf::Vector2f(GAME_SIZE_X, GAME_SIZE_Y)));

	stateMainMenu = new StateMainMenu();
	stateLevel    = new StateLevel();
	stateCombat   = new StateCombat();

	State::setDefaultState(stateLevel);
}

void Game::QuitGame()
{
	window.close();
}

Map Game::getCurrentMap()
{
	return *currentMap;
}
