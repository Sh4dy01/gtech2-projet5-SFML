#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

class Entity {

public:

	Entity(sf::String, sf::Vector2f);
	void SetSprite(sf::IntRect);

	sf::Sprite GetSprite() { return _sprite; };

protected:

	sf::String name;

	sf::Sprite _sprite;
	sf::Texture _texture;

	sf::Vector2f pos;

};