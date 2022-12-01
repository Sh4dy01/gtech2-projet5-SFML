#include "PokemonWorld.h"
#include "Manager/Game.h"
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

	bool IsSameX = this->getPosition().x == player->getPosition().x;
	bool IsSameY = this->getPosition().y == player->getPosition().y;
	int distX = (player->getPosition().x - this->getPosition().x) / SPRITE_SIZE;
	int distY = (player->getPosition().y - this->getPosition().y) / SPRITE_SIZE;
	
	switch (currentDirection)
	{
	case LEFT:
		if (IsSameY && distX <= 0 && abs(distX) <= range)
			return true;
		break;

	case UP:
		if (IsSameX && distY <= 0 && abs(distY) <= range)
			return true;
		break;

	case RIGHT:
		if (IsSameY && distX >= 0 && abs(distX) <= range)
			return true;
		break;

	case DOWN:
		if (IsSameX && distY >= 0 && abs(distY) <= range)
			return true;
		break;
	}
	
	return false;
}

void PokemonWorld::FindAndSetDetectionRange()
{
	int range = 0;
	int x = getPosition().x / SPRITE_SIZE;
	int y = getPosition().y / SPRITE_SIZE;


	while (!Game::getInstance().getMap().thereIsCollision(x-1, y-1, currentDirection))
	{
		range++;

		switch (currentDirection)
		{
		case LEFT:
			x--;
			break;
		case UP:
			y--;
			break;
		case RIGHT:
			x++;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
		}
	}

	std::cout << name << " has " << range << " range" << std::endl << std::endl;

	this->range = range;
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
		this->move(-speed*d, 0.0f);
		nextAnimation = WALK_LEFT;
		this->setScale(sf::Vector2f(1.0f, 1.0f));
		isMoving = true;
		break;
	case UP:
		this->move(0.0f, -speed * d);
		nextAnimation = WALK_UP;
		isMoving = true;
		break;
	case RIGHT:
		this->move(speed * d, 0.0f);
		nextAnimation = WALK_LEFT;
		isMoving = true;
		this->setScale(sf::Vector2f(-1.0f, 1.0f));
		break;
	case DOWN:
		this->move(0.0f, speed * d);
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
