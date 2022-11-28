#include "Manager/Game.h"
#include "Manager/PlayerController.h"
#include "UIMainMenu.h"

#include "Manager/Resource/ResourceManager.h"

#include "Manager/SpriteConfig.h"
#include <iostream>

sf::Color outlineColor = sf::Color(228, 172, 34, 255);
float outlineThickness = 1.0f;

UIMainMenu::UIMainMenu()
	: opacity(0.0F), elem(TITLE), pos(3), isButtonsDrew(false), musicVolume(Game::getInstance().getMusicManager().GetVolume()), soundVolume(Game::getInstance().getSoundManager().GetVolume())
{
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

	musicVolumeText.setFont(font);
	musicVolumeText.setString("Music volume : " + to_string(musicVolume) + "%");
	musicVolumeText.setCharacterSize(8);
	musicVolumeText.setPosition((start.getPosition().x - musicVolumeText.getLocalBounds().width / 2), start.getPosition().y);
	musicVolumeText.setFillColor(sf::Color(255, 255, 255, 0));
	musicVolumeText.setOutlineThickness(0.0f);
	musicVolumeText.setOutlineColor(outlineColor);
	elements.push_back(&musicVolumeText);

	soundVolumeText.setFont(font);
	soundVolumeText.setString("Sound volume : " + to_string(soundVolume) + "%");
	soundVolumeText.setCharacterSize(8);
	soundVolumeText.setPosition((options.getPosition().x - soundVolumeText.getLocalBounds().width / 2), options.getPosition().y);
	soundVolumeText.setFillColor(sf::Color(255, 255, 255, 0));
	soundVolumeText.setOutlineThickness(0.0f);
	soundVolumeText.setOutlineColor(outlineColor);
	elements.push_back(&soundVolumeText);

	applySettings.setFont(font);
	applySettings.setString("Apply");
	applySettings.setCharacterSize(8);
	applySettings.setPosition((quit.getPosition().x - applySettings.getLocalBounds().width / 2), quit.getPosition().y);
	applySettings.setFillColor(sf::Color(255, 255, 255, 0));
	applySettings.setOutlineThickness(0.0f);
	applySettings.setOutlineColor(outlineColor);
	elements.push_back(&applySettings);

	player.Initialize(1, sf::Vector2i(0, 8));
	elements.push_back(&player);
}
	

void UIMainMenu::step(double d)
{
	if (logo.getPosition().y < 0)
	{
		logo.move(0, 75 * d * 2);
	}

	if (!isSettingsView)
	{
		player.CheckLateralDirections(d);
	}

	switch (isButtonsDrew)
	{
	case false:
		DrawButtons(d);
		break;
	case true:
		CheckButtonsInput();
		inputDelay += d;
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
	if (inputDelay >= INPUT_DELAY)
	{
		inputDelay = INPUT_DELAY;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {
			UpdateTextOutline(pos, 0);
			pos--;
			ChangeSelectedButton();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
			UpdateTextOutline(pos, 0);
			pos++;
			ChangeSelectedButton();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q) && isSettingsView) {
			switch (pos)
			{
			case MUSIC:
				musicVolume -= 5;
				UpdateTextElement(pos, "Music volume : " + to_string(musicVolume) + "%");
				break;
			case SOUND:
				soundVolume -= 5;
				UpdateTextElement(pos, "Sound volume : " + to_string(soundVolume) + "%");
				break;
			}

			ResetInputDelay();
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && isSettingsView) {
			switch (pos)
			{
			case MUSIC:
				musicVolume += 5;
				UpdateTextElement(pos, "Music volume : " + to_string(musicVolume) + "%");
				break;
			case SOUND:
				soundVolume += 5;
				UpdateTextElement(pos, "Sound volume : " + to_string(soundVolume) + "%");
				break;
			}

			ResetInputDelay();
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
			case QUIT:
				QuitTheGame();
			case APPLY:
				ApplySettings();
			default:
				break;
			}

			ResetInputDelay();
		}
	}
}

void UIMainMenu::ChangeSelectedButton() {
	std::cout << pos << std::endl;

	if (!isSettingsView)
	{
		if (pos < START)
			pos = QUIT;
		else if (pos > QUIT)
			pos = START;
	}
	else {
		if (pos < MUSIC)
			pos = APPLY;
		else if (pos > APPLY)
			pos = MUSIC;
	}

	Game::getInstance().getSoundManager().PlaySound("select-sound");
	UpdateTextOutline(pos, outlineThickness);
	ResetInputDelay();
}

void UIMainMenu::GoToMainGame() {
	State::switchState(Game::getInstance().stateCombat);
	//State::switchState(Game::getInstance().stateLevel);
}

void UIMainMenu::GoToSettings() {
	isSettingsView = true;

	start.setFillColor(sf::Color(255, 255, 255, 0));
	options.setFillColor(sf::Color(255, 255, 255, 0));
	UpdateTextOutline(SETTINGS, 0);
	quit.setFillColor(sf::Color(255, 255, 255, 0));

	UpdateTextOutline(MUSIC, outlineThickness);
	musicVolumeText.setFillColor(sf::Color(255, 255, 255, 255));
	soundVolumeText.setFillColor(sf::Color(255, 255, 255, 255));
	applySettings.setFillColor(sf::Color(255, 255, 255, 255));

	pos = MUSIC;
}

void UIMainMenu::ApplySettings()
{
	isSettingsView = false;

	start.setFillColor(sf::Color(255, 255, 255, 255));
	UpdateTextOutline(START, outlineThickness);
	options.setFillColor(sf::Color(255, 255, 255, 255));
	quit.setFillColor(sf::Color(255, 255, 255, 255));

	musicVolumeText.setFillColor(sf::Color(255, 255, 255, 0));
	soundVolumeText.setFillColor(sf::Color(255, 255, 255, 0));
	applySettings.setFillColor(sf::Color(255, 255, 255, 0));
	UpdateTextOutline(APPLY, 0);

	pos = START;

	Game::getInstance().getMusicManager().SetVolume(musicVolume);
	Game::getInstance().getSoundManager().SetVolume(soundVolume);
}

void UIMainMenu::QuitTheGame() {
	Game::getInstance().QuitGame();
}