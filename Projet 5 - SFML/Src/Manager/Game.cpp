#include "Game.h"


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


	stateMainMenu = new StateMainMenu();
	stateLevel    = new StateLevel();
	stateCombat   = new StateCombat();

	State::setDefaultState(stateMainMenu);
}
