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
	uiMainMenu->render(Game::getInstance().getWindow());
}
