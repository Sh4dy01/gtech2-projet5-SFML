#pragma once

#include <vector>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Widget;

namespace sf { class RenderWindow; }


class UI
{
public:

	UI();

	virtual void step(double d);

	void render(sf::RenderWindow& window );


protected:

	double count;
	std::vector<sf::Drawable*> elements;
};
