#pragma once

#include "UI/Widget.h"

// Forward declarations.
namespace sf { class Texture; class Sprite; }


class Panel : public Widget
{
public:

	Panel();

	virtual void render(sf::RenderWindow* w) override;

	void setTexture(sf::Texture* t);


private:

		/// Optional SFML texture and sprite.
	sf::Sprite* sprite;
};
