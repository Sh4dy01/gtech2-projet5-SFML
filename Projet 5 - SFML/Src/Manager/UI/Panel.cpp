#include "Panel.h"

#include <SFML/Graphics.hpp>


Panel::Panel()
	: sprite(0)
{
	
}

void Panel::render(sf::RenderWindow& w)
{
	w.draw(*sprite);
}

void Panel::setTexture(sf::Texture* t)
{
	sprite->setTexture(*t);
}
