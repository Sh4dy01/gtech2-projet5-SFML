#include "UI.h"

#include "Widget.h"


UI::UI()
{

}

void UI::step(double d)
{

}

void UI::render(sf::RenderWindow& window)
{
	for (sf::Drawable* e : elements) {
		window.draw(*e);
	}
}