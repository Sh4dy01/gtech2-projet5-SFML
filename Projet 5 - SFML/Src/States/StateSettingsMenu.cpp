#include "Manager/Game.h"

#include "StateSettingsMenu.h"
#include "UI/UISettingsMenu.h"

StateSettingsMenu::StateSettingsMenu() 
{
	uiSettingsMenu = 0;
}

void StateSettingsMenu::enter()
{
	uiSettingsMenu = new UISettingsMenu();
}

void StateSettingsMenu::leave()
{
	delete uiSettingsMenu;
}

void StateSettingsMenu::update(double deltaTime)
{
	uiSettingsMenu->step(deltaTime);
}

void StateSettingsMenu::render()
{
	uiSettingsMenu->render(Game::getInstance().getWindow());
}