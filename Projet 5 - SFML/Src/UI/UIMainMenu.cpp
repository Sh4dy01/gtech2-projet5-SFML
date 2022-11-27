#include "Manager/Game.h"
#include "Manager/PlayerController.h"
#include "UIMainMenu.h"

#include "Manager/Resource/ResourceManager.h"

#include "Manager/SpriteConfig.h"
#include <iostream>

sf::Color outlineColor = sf::Color(228, 172, 34, 255);
float outlineThickness = 1.0f;

UIMainMenu::UIMainMenu()
	: opacity(0.0F), elem(TITLE), pos(3), isButtonsDrew(false)
{
	count = 1.0;
	sf::Texture& logoTexture = Game::getInstance().getResourceManager().loadImage("pokemon-title.png");
	sf::Texture& bgTexture = Game::getInstance().getResourceManager().loadImage("title-bg.jpg");
	//logoTexture.setSmooth(false);
	sf::Font& font = Game::getInstance().getResourceManager().loadFont("Pokemon-Classic.ttf");
	((sf::Texture&)font.getTexture(8)).setSmooth(false);

	sf::Sprite* bg = new sf::Sprite();
	bg->setTexture(bgTexture);
	bg->setScale(sf::Vector2f(1.20f, 1.20f));
	elements.push_back(bg);

	logo.setScale(sf::Vector2f(0.2F, 0.2F));
	logo.setTexture(logoTexture);
	logo.setColor(sf::Color(255, 255, 255, 0));
	logo.setPosition(GAME_SIZE_X / 2 - logo.getGlobalBounds().width / 2, -logo.getGlobalBounds().height);
	elements.push_back(&logo);

	subtitle.setString("ORIGINS");
	subtitle.setFont(font);
	subtitle.setCharacterSize(16);
	subtitle.setPosition((GAME_SIZE_X - subtitle.getLocalBounds().width) / 2, -logo.getPosition().y);
	subtitle.setFillColor(sf::Color(0, 0, 0, 0));
	elements.push_back(&subtitle);

	start.setFont(font);
	start.setString("Start");
	start.setCharacterSize(8);
	start.setPosition((GAME_SIZE_X - start.getLocalBounds().width) / 2, GAME_SIZE_Y/2 + 30);
	start.setFillColor(sf::Color(0, 0, 0, 0));
	start.setOutlineThickness(outlineThickness);
	start.setOutlineColor(sf::Color(228, 172, 34, 0));
	elements.push_back(&start);

	options.setFont(font);
	options.setString("Settings");
	options.setCharacterSize(8);
	options.setPosition((GAME_SIZE_X - options.getLocalBounds().width) / 2, start.getPosition().y + start.getLocalBounds().height + 10);
	options.setFillColor(sf::Color(0, 0, 0, 0));
	options.setOutlineThickness(0.0f);
	options.setOutlineColor(outlineColor);
	elements.push_back(&options);

	quit.setFont(font);
	quit.setString("Quit");
	quit.setCharacterSize(8);
	quit.setPosition((GAME_SIZE_X - quit.getLocalBounds().width) / 2, options.getPosition().y + quit.getLocalBounds().height + 10);
	quit.setFillColor(sf::Color(0, 0, 0, 0));
	quit.setOutlineThickness(0.0f);
	quit.setOutlineColor(outlineColor);
	elements.push_back(&quit);

	player.Initialize(1, sf::Vector2i(0, 8));
	elements.push_back(&player);
}
	

void UIMainMenu::step(double d)
{
	if (logo.getPosition().y < 0)
	{
		logo.move(0, 75 * d * 2);
	}

	player.CheckLateralDirections(d);


	switch (isButtonsDrew)
	{
	case false:
		DrawButtons(d);
		break;
	case true:
		CheckButtonsInput();
		count += d;
		break;
	}
}

void UIMainMenu::DrawButtons(double d)
{
	switch (elem)
	{
	case TITLE:
		logo.setColor(sf::Color(255, 255, 255, opacity));
		break;
	case SUBTITLE:
		subtitle.setFillColor(sf::Color(0, 0, 0, opacity));
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

	if (elem > QUIT) isButtonsDrew = true;
}

void UIMainMenu::CheckButtonsInput()
{
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
}

void UIMainMenu::ChangeTextOutline() {
	std::cout << pos << std::endl;

	if (pos < START)
		pos = QUIT;
	else if (pos > QUIT)
		pos = START;

	((sf::Text*)elements[pos])->setOutlineThickness(outlineThickness);

	count = 0;
}

void UIMainMenu::GoToMainGame() {
	State::switchState(Game::getInstance().stateLevel);
}

void UIMainMenu::GoToSettings() {
	State::switchState(Game::getInstance().stateSettingsMenu);
}