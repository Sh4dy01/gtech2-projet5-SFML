#include "Entity.h"
#include "Manager/SpriteConfig.h"
#include <iostream>s

Entity::Entity(sf::String name) : name(name)
{
}


void Entity::Initialize(sf::IntRect region, int scale, sf::Vector2i spawn) 
{
	this->SetSprite(region);
	this->setScale(sf::Vector2f(scale, scale));
	this->SetSpawn(sf::Vector2f(spawn));
}

void Entity::SetSprite(sf::IntRect rect)
{
	std::cout << name.toAnsiString();
	_texture.loadFromFile(BASE_TEXTURE_PATH + name + ".png", rect);
	this->setTexture(_texture);
}

void Entity::SetSpawn(sf::Vector2f spawn)
{
	spawn.x *= SPRITE_SIZE;
	spawn.y *= SPRITE_SIZE;
	this->setPosition(spawn);
}
