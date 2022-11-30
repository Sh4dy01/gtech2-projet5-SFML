#include "PokemonWorld.h"
#include <iostream>

PokemonWorld::PokemonWorld(int pokedexNumber) : pokemon(PokemonRegistry::getPokemonByPokedexNumber(pokedexNumber)), AnimatedEntity(animations, name, true)
{
	if (pokemon)
	{
		this->name = pokemon->getName();
		this->animations = pokemon->getAnimations();
	}

	speed = 0.5f;
}

bool PokemonWorld::IsPlayerDetected(Player* player) {
	switch (currentDirection)
	{
	case LEFT:
		if (this->getPosition().y == player->getPosition().y && 
			player->getPosition().x < this->getPosition().x)
		{
			return true;
		}
		break;
	case UP:
		if (this->getPosition().x == player->getPosition().x && 
			player->getPosition().y < this->getPosition().y)
		{
			return true;
		}
		break;
	case RIGHT:
		if (this->getPosition().y == player->getPosition().y && 
			player->getPosition().x > this->getPosition().x)
		{
			return true;
		}
		break;
	case DOWN:
		if (this->getPosition().x == player->getPosition().x && 
			player->getPosition().y > this->getPosition().y)
		{
			return true;
		}
		break;
	}
	
	return false;
}

void PokemonWorld::Move(double d)
{
	switch (currentDirection)
	{
	case STILL:
		StopCurrentAnimation();
		isMoving = false;
		break;
	case LEFT:
		this->move(-speed, 0.0f);
		nextAnimation = WALK_LEFT;
		this->setScale(sf::Vector2f(1.0f, 1.0f));
		isMoving = true;
		break;
	case UP:
		this->move(0.0f, -speed);
		nextAnimation = WALK_UP;
		isMoving = true;
		break;
	case RIGHT:
		this->move(speed, 0.0f);
		nextAnimation = WALK_LEFT;
		isMoving = true;
		this->setScale(sf::Vector2f(-1.0f, 1.0f));
		break;
	case DOWN:
		this->move(0.0f, speed);
		nextAnimation = WALK_DOWN;
		isMoving = true;
		break;
	}

	if (IsSnappedToGrid() && currentDirection != nextDirection)
	{
		currentDirection = nextDirection;
	}

	if (currentAnimation != nextAnimation)
	{
		currentAnimation = nextAnimation;
	}

	if (count >= 0.2)
	{
		NextAnimationFrame();
		count = 0;
	}

	count += d;
}

void PokemonWorld::StopCurrentAnimation(void)
{
	this->pos = 0;
	this->setTextureRect(animations[this->currentAnimation][this->pos]);
}
