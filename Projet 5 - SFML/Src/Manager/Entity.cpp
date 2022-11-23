#include "Entity.h"
#include "Manager/SpriteConfig.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

Entity::Entity(sf::String name) : name(name)
{
}

void Entity::SetSprite(sf::IntRect rect)
{
	std::cout << name.toAnsiString();
	_texture.loadFromFile(BASE_TEXTURE_PATH + name + ".png", rect);
	this->setTexture(_texture);
}

void Entity::SetSpawn(sf::Vector2f spawn)
{
	this->setPosition(spawn);
}
