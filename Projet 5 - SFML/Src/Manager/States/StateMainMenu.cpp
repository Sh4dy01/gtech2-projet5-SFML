#include "Manager/Game.h"
#include "StateMainMenu.h"

#include "Manager/UI/UIMainMenu.h"


StateMainMenu::StateMainMenu()
{
	uiMainMenu = 0;
}

void StateMainMenu::enter()
{
	uiMainMenu = new UIMainMenu();
}

void StateMainMenu::leave()
{
	delete uiMainMenu;
}

void StateMainMenu::update(double deltaTime)
{
	uiMainMenu->step(deltaTime);
}

void StateMainMenu::render()
{
	uiMainMenu->render(Game::getWindow());
}
