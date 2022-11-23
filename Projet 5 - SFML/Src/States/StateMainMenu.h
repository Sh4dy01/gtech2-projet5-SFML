#pragma once

#include "State/State.h"

class UIMainMenu;


class StateMainMenu : public State
{
public:

	StateMainMenu();

	virtual void enter() override;
	virtual void leave() override;

	virtual void update(double deltaTime) override;
	virtual void render() override;


private:

	UIMainMenu* uiMainMenu;
};
