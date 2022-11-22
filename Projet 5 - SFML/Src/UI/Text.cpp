#include "Text.h"

#include <SFML/Graphics.hpp>


Text::Text()
{

}

void Text::render(sf::RenderWindow* w)
{
	w->draw(*text);
}