#include "Manager/Game.h"
#include "Manager/PlayerController.h"
#include "UIMainMenu.h"

#include "Manager/Resource/ResourceManager.h"

#include "Manager/SpriteConfig.h"
#include <iostream>


UIMainMenu::UIMainMenu()
	: s_title_o(0.0F), s_origins_o(0.0F)
{
	sf::Texture& logoTexture = Game::getInstance().getResourceManager().loadImage("pokemon-title.png");
	//logoTexture.setSmooth(false);
	sf::Font& font = Game::getInstance().getResourceManager().loadFont("Pokemon-Classic.ttf");
	((sf::Texture&)font.getTexture(8)).setSmooth(false);

	logo.setScale(sf::Vector2f(0.2F, 0.2F));
	logo.setTexture(logoTexture);
	logo.setColor(sf::Color(0, 0, 0, 0));
	logo.setPosition(GAME_SIZE_X / 2 - logo.getGlobalBounds().width / 2, -logo.getGlobalBounds().height);

	subtitle.setString("Origins");
	subtitle.setFont(font);
	subtitle.setCharacterSize(8);
	subtitle.setPosition((GAME_SIZE_X - subtitle.getLocalBounds().width) / 2, logo.getGlobalBounds().height);
	subtitle.setFillColor(sf::Color(0, 0, 0, 0));

	player.Initialize(
		1,
		sf::Vector2i(0, 0)
	);

	debug.setFont(font);
	debug.setCharacterSize(8);
	debug.setPosition(4, GAME_SIZE_Y - 12);
	debug.setFillColor(sf::Color(255, 255, 255, 255));
}
	

void UIMainMenu::step(double d)
{
	if (logo.getPosition().y < 0)
	{
		logo.move(0, 75 * d);
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

void UIMainMenu::render(sf::RenderWindow& window)
{
	UI::render(window);
	window.draw(logo);
	window.draw(subtitle);
	window.draw(player);
	window.draw(debug);
}
