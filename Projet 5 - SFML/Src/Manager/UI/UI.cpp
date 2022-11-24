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
	for (Widget* w : widgets) {
		w->render(window);
	}
}

void UI::addWidget(Widget* w)
{
	this->widgets.push_back(w);
	w->owner = this;
}
