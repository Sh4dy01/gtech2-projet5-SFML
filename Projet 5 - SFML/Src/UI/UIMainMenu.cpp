#include "Manager/Game.h"
#include "Manager/PlayerController.h"
#include "UIMainMenu.h"

#include "Manager/SpriteConfig.h"
#include <iostream>

UIMainMenu::UIMainMenu()
	: s_title_o(0.0F), s_origins_o(0.0F)
{
	logoTexture.loadFromFile("Assets/Images/pokemon-title.png");
	logoTexture.setSmooth(false);

	logo.setTexture(logoTexture);
	logo.setColor(sf::Color(0, 0, 0, 0));
	logo.setPosition(Game::GetWidth() / 2 - logo.getLocalBounds().width / 2, -logo.getLocalBounds().height);

	font.loadFromFile("Assets/Fonts/Pokemon-Classic.ttf");

	subtitle.setString("Origins");
	subtitle.setFont(font);
	subtitle.setCharacterSize(50);
	subtitle.setPosition(Game::GetWidth() / 2 - subtitle.getLocalBounds().width / 2, logo.getLocalBounds().height);
	subtitle.setFillColor(sf::Color(0, 0, 0, 0));

	player.Initialize(
		sf::IntRect(1, 1, SPRITE_SIZE, SPRITE_SIZE),
		1,
		sf::Vector2i(0, 0)
	);

	debug.setString("x:"+std::to_string(int(player.getPosition().x)) + " y:" + std::to_string(int(player.getPosition().y)));
	debug.setFont(font);
	debug.setCharacterSize(30);
	debug.setPosition(0, Game::GetHeight() - debug.getLocalBounds().height);
	debug.setFillColor(sf::Color(255, 255, 255, 255));
}
	

void UIMainMenu::step(double d)
{
	if (logo.getPosition().y < 0)
	{
		logo.move(0, 320 * d);
	}
	if (s_title_o < 255)
	{
		logo.setColor(sf::Color(255, 255, 255, s_title_o));
		s_title_o += 255 * d;
	}
	else if (s_origins_o < 255) {
		subtitle.setFillColor(sf::Color(255, 255, 255, s_origins_o));
		s_origins_o += 255 * d;
	}

	player.CheckDirection();
	debug.setString("x:" + std::to_string(int(player.getPosition().x)) + " y:" + std::to_string(int(player.getPosition().y)));
}

void UIMainMenu::render(sf::RenderWindow* window)
{
	UI::render(window);

	window->draw(logo);
	window->draw(subtitle);
	window->draw(player);
	window->draw(debug);
}
