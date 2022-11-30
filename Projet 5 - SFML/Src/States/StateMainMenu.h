#pragma once

#include "Manager/State/State.h"
#include "Manager/PlayerController.h"

class UIMainMenu;


class StateMainMenu : public State
{
public:

	StateMainMenu();

	virtual void enter() override;
	virtual void leave() override;

	virtual void update(double deltaTime) override;
	virtual void render(sf::RenderWindow& window) override;


private:

	UIMainMenu* uiMainMenu;
};
