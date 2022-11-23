#pragma once

#include "Manager/UI/UI.h"

#include <SFML/Graphics.hpp>


class UIMainMenu : public UI
{
public:

	UIMainMenu();

	virtual void step(double d) override;

	virtual void render(sf::RenderWindow* window) override;

private:

	sf::Sprite logo;
	sf::Text   subtitle;

	// TODO : move these to their respective resource manager.
	sf::Texture logoTexture;
	sf::Font font;

	float s_title_o;
	float s_origins_o;
};
