#pragma once

#include "Manager/UI/UI.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

enum element {
	TITLE = 0,
	SUBTITLE = 1,
	START = 2,
	SETTINGS = 3,
	QUIT = 4
};

class UISettingsMenu : public UI
{
public:

	UISettingsMenu();

	virtual void step(double d) override;
	void ChangeTextOutline();
	void GoToMainGame();

private:

	int elem;
	int pos;
	float opacity;

};
