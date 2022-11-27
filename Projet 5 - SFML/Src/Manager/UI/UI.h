#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#define INPUT_DELAY 0.2

class Widget;

namespace sf { class RenderWindow; }


class UI
{
public:

	UI();

	virtual void step(double d);
	void UpdateTextElement(int elem, sf::String);
	void UpdateTextOutline(int elem, float thickness);
	void ResetInputDelay() { inputDelay = 0; };

	void render(sf::RenderWindow& window );


protected:

	double inputDelay;
	std::vector<sf::Drawable*> elements;
};
