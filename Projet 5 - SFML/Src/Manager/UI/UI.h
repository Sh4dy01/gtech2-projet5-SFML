#pragma once

#include <vector>

class Widget;

namespace sf { class RenderWindow; }


class UI
{
public:

	UI();

	virtual void step(double d);

	virtual void render(sf::RenderWindow* window );

	void addWidget(Widget* w);



private:

	std::vector<Widget*> widgets;
};
