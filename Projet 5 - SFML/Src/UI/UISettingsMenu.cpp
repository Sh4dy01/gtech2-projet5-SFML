#include "Manager/Game.h"
#include "UISettingsMenu.h"

#include "Manager/Resource/ResourceManager.h"

#include "Manager/SpriteConfig.h"
#include <iostream>

UISettingsMenu::UISettingsMenu()
{
	
}


void UISettingsMenu::step(double d)
{
	
}

void UISettingsMenu::ChangeTextOutline() {
	std::cout << pos << std::endl;

	if (pos < 2)
		pos = 4;
	else if (pos > 4)
		pos = 2;


	count = 0;
}


void UISettingsMenu::GoToMainGame() {
	State::switchState(Game::getInstance().stateLevel);
}