#include "Entity.h"
#include "Game.h"
#include "Manager/SpriteConfig.h"
#include <iostream>s

Entity::Entity(std::string name, bool isPokemon) : name(name), isPokemon(isPokemon)
{
}


void Entity::Initialize(sf::IntRect region, float scale, sf::Vector2i spawn) 
{
	this->SetSprite();
	this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
	this->setScale(sf::Vector2f(scale, scale));
	this->SetSpawn(sf::Vector2f(spawn));
	this->setTextureRect(region);
}

void Entity::SetSprite()
{
	_texture = Game::getInstance().getResourceManager().loadSprite(name.c_str(), isPokemon);
	this->setTexture(_texture);
}

void Entity::SetSpawn(sf::Vector2f spawn)
{
	spawn.x *= SPRITE_SIZE;
	spawn.y *= SPRITE_SIZE;

	this->setPosition(spawn);
	std::cout << "Spawned " << this->name << " at " << this->getPosition().x/SPRITE_SIZE << ":" << this->getPosition().y/ SPRITE_SIZE << std::endl;
}

void Entity::PrintCoords() {
	std::cout << name << " : " << this->getPosition().x << ", " << this->getPosition().y << std::endl;
}
