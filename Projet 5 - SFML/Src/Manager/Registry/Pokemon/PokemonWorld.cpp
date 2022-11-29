#include "PokemonWorld.h"
#include <iostream>
#include "PokemonRegistry.h"

PokemonWorld::PokemonWorld(int pokedexNumber) : AnimatedEntity(animations, name, true)
{
	pokemon = PokemonRegistry::getPokemonByPokedexNumber(pokedexNumber);
	//this->name = pokemon->getName();
	std::cout << name.toAnsiString();
	speed = 0.5f;
}

void PokemonWorld::Move(double d)
{
	switch (currentDirection)
	{
	case STILL:
		this->move(0.0f, 0.0f);
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
