#include "UI.h"
#include "Widget.h"

#include "Manager/Game.h"


UI::UI()
{
	Game::getInstance().getSoundManager().LoadSound("select-sound");
}

void UI::step(double d)
{
	if (inputDelay >= INPUT_DELAY)
		inputDelay = INPUT_DELAY;
}

void UI::UpdateTextElement(int elem, sf::String text)
{
	((sf::Text*)elements[elem])->setString(text);
}

void UI::UpdateTextOutline(int elem, float thickness)
{
	((sf::Text*)elements[elem])->setOutlineThickness(thickness);
}

void UI::render(sf::RenderWindow& window)
{
	for (sf::Drawable* e : elements) {
		window.draw(*e);
	}
}