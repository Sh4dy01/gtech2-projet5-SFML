#pragma once

#include "Manager/UI/UI.h"
#include "Manager/AnimatedEntity.h"
#include "Manager/PlayerController.h"

#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

enum element {
	TITLE = 0,
	SUBTITLE = 1,
	START = 3,
	SETTINGS = 4,
	QUIT = 5,
	MUSIC = 6,
	SOUND = 7,
	APPLY = 8
};

class UIMainMenu : public UI
{
public:

	UIMainMenu();

	virtual void step(double d) override;
	void DrawButtons(double d);
	void CheckButtonsInput();
	void ChangeSelectedButton();

	void GoToMainGame();
	void GoToSettings();
	void ApplySettings();
	void QuitTheGame();

private:

	bool isButtonsDrew;
	bool isSettingsView;

	int elem;
	int pos;
	float opacity;

	int musicVolume;
	int soundVolume;

	Player player;
	
	sf::Sprite	logo;
	sf::Text	subtitle;
	sf::Text	start;
	sf::Text	options;
	sf::Text	quit;

	sf::Text	musicVolumeText;
	sf::Text	soundVolumeText;
	sf::Text	applySettings;
};
