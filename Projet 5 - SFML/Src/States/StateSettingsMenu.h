#pragma once

#include "Manager/State/State.h"

class UISettingsMenu;


class StateSettingsMenu : public State
{
public:

	StateSettingsMenu();

	virtual void enter() override;
	virtual void leave() override;

	virtual void update(double deltaTime) override;
	virtual void render() override;


private:

	UISettingsMenu* uiSettingsMenu;
};
