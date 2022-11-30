#include "PokemonWorld.h"
#include <iostream>

PokemonWorld::PokemonWorld(int pokedexNumber) : pokemon(PokemonRegistry::getPokemonByPokedexNumber(pokedexNumber)), AnimatedEntity(animations, name, true)
{
	if (pokemon)
	{
		this->name = pokemon->getName();
		this->animations = pokemon->getAnimations();
		range = GetDetectionRange();
	}

	speed = 0.5f;
}

bool PokemonWorld::IsPlayerDetected(Player* player) {

	bool IsSameX = this->getPosition().x == player->getPosition().x;
	bool IsSameY = this->getPosition().y == player->getPosition().y;
	int distX = (this->getPosition().x - player->getPosition().x) / SPRITE_SIZE;
	int distY = (this->getPosition().y - player->getPosition().y) / SPRITE_SIZE;

	switch (currentDirection)
	{
	case LEFT:
		if (IsSameY && distX <= range)
		{
			return true;
		}
		break;
	case UP:
		if (IsSameX && distY <= range)
		{
			return true;
		}
		break;
	case RIGHT:
		if (IsSameY && -distX <= range)
		{
			return true;
		}
		break;
	case DOWN:
		if (IsSameX && distY <= range)
		{
			return true;
		}
		break;
	}
	
	return false;
}

int PokemonWorld::GetDetectionRange()
{
	return 5;
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
