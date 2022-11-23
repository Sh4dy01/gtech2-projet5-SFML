#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

class Entity : public sf::Sprite {

public:

	Entity(sf::String);
	void SetSprite(sf::IntRect);
	void SetSpawn(sf::Vector2f spawn);

protected:

	sf::String name;
	sf::Texture _texture;
};