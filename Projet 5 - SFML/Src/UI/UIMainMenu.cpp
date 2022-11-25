#include "Manager/Game.h"
#include "Manager/PlayerController.h"
#include "UIMainMenu.h"

#include "Manager/Resource/ResourceManager.h"

#include "Manager/SpriteConfig.h"
#include <iostream>

sf::Color outlineColor = sf::Color(228, 172, 34, 255);
float outlineThickness = 1.0f;

UIMainMenu::UIMainMenu()
	: opacity(0.0F), elem(TITLE), pos(2)
{
	count = 1.0;
	sf::Texture& logoTexture = Game::getInstance().getResourceManager().loadImage("pokemon-title.png");
	//logoTexture.setSmooth(false);
	sf::Font& font = Game::getInstance().getResourceManager().loadFont("Pokemon-Classic.ttf");
	((sf::Texture&)font.getTexture(8)).setSmooth(false);

	logo.setScale(sf::Vector2f(0.2F, 0.2F));
	logo.setTexture(logoTexture);
	logo.setColor(sf::Color(255, 255, 255, 0));
	logo.setPosition(GAME_SIZE_X / 2 - logo.getGlobalBounds().width / 2, -logo.getGlobalBounds().height);
	elements.push_back(&logo);

	subtitle.setString("Origins");
	subtitle.setFont(font);
	subtitle.setCharacterSize(8);
	subtitle.setPosition((GAME_SIZE_X - subtitle.getLocalBounds().width) / 2, -logo.getPosition().y);
	subtitle.setFillColor(sf::Color(0, 0, 0, 0));
	elements.push_back(&subtitle);

	start.setFont(font);
	start.setString("Start game");
	start.setCharacterSize(8);
	start.setPosition((GAME_SIZE_X - start.getLocalBounds().width) / 2, GAME_SIZE_Y/2);
	start.setFillColor(sf::Color(0, 0, 0, 0));
	start.setOutlineThickness(outlineThickness);
	start.setOutlineColor(sf::Color(228, 172, 34, 0));
	elements.push_back(&start);

	options.setFont(font);
	options.setString("settings");
	options.setCharacterSize(8);
	options.setPosition((GAME_SIZE_X - options.getLocalBounds().width) / 2, start.getPosition().y + start.getLocalBounds().height + 10);
	options.setFillColor(sf::Color(0, 0, 0, 0));
	options.setOutlineThickness(0.0f);
	options.setOutlineColor(outlineColor);
	elements.push_back(&options);

	quit.setFont(font);
	quit.setString("quit");
	quit.setCharacterSize(8);
	quit.setPosition((GAME_SIZE_X - quit.getLocalBounds().width) / 2, options.getPosition().y + quit.getLocalBounds().height + 10);
	quit.setFillColor(sf::Color(0, 0, 0, 0));
	quit.setOutlineThickness(0.0f);
	quit.setOutlineColor(outlineColor);
	elements.push_back(&quit);

	/*player.Initialize(1, sf::Vector2i(1, 1));
	elements.push_back(&player);*/
}
	

void UIMainMenu::step(double d)
{
	if (logo.getPosition().y < 0)
	{
		logo.move(0, 75 * d * 2);
	}

	//player.CheckDirection(d);

	if (elem <= 4)
	{
		switch (elem)
		{
		case TITLE:
			logo.setColor(sf::Color(255, 255, 255, opacity));
			break;
		case SUBTITLE:
			subtitle.setFillColor(sf::Color(255, 255, 255, opacity));
			break;
		case START:
			start.setFillColor(sf::Color(255, 255, 255, opacity));
			start.setOutlineColor(sf::Color(228, 172, 34, opacity));
			break;
		case SETTINGS:
			options.setFillColor(sf::Color(255, 255, 255, opacity));
			break;
		case QUIT:
			quit.setFillColor(sf::Color(255, 255, 255, opacity));
			break;
		default:
			break;
		}

		opacity += 255 * (d * 2);
		if (opacity > 255) {
			opacity = 0;
			elem += 1;
		}
	}

	if (count >= 0.2)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			((sf::Text*)elements[pos])->setOutlineThickness(0.0f);
			pos--;
			ChangeTextOutline();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			((sf::Text*)elements[pos])->setOutlineThickness(0.0f);
			pos++;
			ChangeTextOutline();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			switch (pos)
			{
			case START:
				GoToMainGame();
				break;
			case SETTINGS:
				GoToSettings();
				break;
			default:
				break;
			}
		}
	}

	count += d;
}

void UIMainMenu::ChangeTextOutline() {
	std::cout << pos << std::endl;

	if (pos < 2)
		pos = 4;
	else if (pos > 4)
		pos = 2;

	((sf::Text*)elements[pos])->setOutlineThickness(outlineThickness);

	count = 0;
}

void UIMainMenu::GoToMainGame() {
	State::switchState(Game::getInstance().stateLevel);
}

void UIMainMenu::GoToSettings() {
	State::switchState(Game::getInstance().stateSettingsMenu);
}