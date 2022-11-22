#pragma once

#include "UI/Widget.h"

namespace sf { class Text; class Font; }


class Text : public Widget
{
public:

	Text();

	virtual void render(sf::RenderWindow* w) override;

	void setFont(sf::Font* f);



private:

	sf::Text* text;
};
