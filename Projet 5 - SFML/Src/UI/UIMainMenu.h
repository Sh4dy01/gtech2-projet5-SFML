#pragma once

#include "Manager/UI/UI.h"
#include "Manager/PlayerController.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

enum element {
	TITLE = 0,
	SUBTITLE = 1,
	START = 2,
	SETTINGS = 3,
	QUIT = 4
};

class UIMainMenu : public UI
{
public:

	UIMainMenu();

	virtual void step(double d) override;
	void ChangeTextOutline();
	void GoToMainGame();
	void GoToSettings();

private:

	int elem;
	int pos;
	float opacity;

	//Player player;
	
	sf::Sprite	logo;
	sf::Text	subtitle;
	sf::Text	start;
	sf::Text	options;
	sf::Text	quit;
};
