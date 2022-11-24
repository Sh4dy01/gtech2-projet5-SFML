#include "Entity.h"
#include "Manager/SpriteConfig.h"
#include <iostream>s

Entity::Entity(sf::String name) : name(name)
{
}


void Entity::Initialize(sf::IntRect region, int scale, sf::Vector2i spawn) 
{
	this->SetSprite();
	this->setScale(sf::Vector2f(BASE_SCALE_FACTOR + scale, BASE_SCALE_FACTOR + scale));
	this->SetSpawn(sf::Vector2f(spawn));
	this->setTextureRect(region);
}

void Entity::SetSprite()
{
	std::cout << name.toAnsiString();
	_texture.loadFromFile(BASE_TEXTURE_PATH + name + ".png");
	this->setTexture(_texture);
}

void Entity::SetSpawn(sf::Vector2f spawn)
{
	spawn.x *= SPRITE_SIZE;
	spawn.y *= SPRITE_SIZE;
	this->setPosition(spawn);
}
