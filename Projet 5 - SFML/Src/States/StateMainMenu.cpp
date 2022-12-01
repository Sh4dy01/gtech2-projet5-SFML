#include "Manager/Game.h"
#include "StateMainMenu.h"

#include "UI/UIMainMenu.h"


StateMainMenu::StateMainMenu()
{
	uiMainMenu = 0;
}

void StateMainMenu::enter()
{
	uiMainMenu = new UIMainMenu();
	Game::getInstance().getMusicManager().LoadMusicAndPlay("main-menu-theme");
}

void StateMainMenu::leave()
{
	Game::getInstance().getMusicManager().StopMusic();
	delete uiMainMenu;
}

void StateMainMenu::update(double deltaTime)
{
	uiMainMenu->step(deltaTime);
}


void StateMainMenu::render(sf::RenderWindow& window)
{
	uiMainMenu->render(Game::getInstance().getWindow());
}
