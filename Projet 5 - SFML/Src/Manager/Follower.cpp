#include "Follower.h"
#include "Game.h"
#include "PlayerController.h"
#include <iostream>
#include <cmath>

#define FOLLOWING_OFFSET  (1.3*SPRITE_SIZE)

Follower::Follower(Player* player, int pokedexNumber) : PokemonWorld(pokedexNumber), player(player)
{
	speed = player->GetSpeed()*0.95;
	currentDirection = player->GetCurrentDirection();
}

void Follower::ChangeFollower(int pokedexNumber)
{
	const PokedexEntry* newPokemon = PokemonRegistry::getPokemonByPokedexNumber(pokedexNumber);

	if (newPokemon)
	{
		this->pokemon = newPokemon;
		this->name = pokemon->getName();
		this->animations = pokemon->getAnimations();
		this->Initialize(FOLLOWER_SCALE, sf::Vector2i(this->getPosition().x/SPRITE_SIZE, this->getPosition().y / SPRITE_SIZE));
	}
}

void Follower::SetToPlayerPosition()
{
	this->setPosition(player->getPosition());
}


void Follower::Move(double d)
{
	sf::Vector2i offset;
	float pathX = player->getPosition().x - this->getPosition().x;
	float pathY = player->getPosition().y - this->getPosition().y;

	if (abs(pathX) > FOLLOWING_OFFSET || abs(pathY) > FOLLOWING_OFFSET) {

		isMoving = true;

		if (pathX > FOLLOWING_OFFSET)
		{
			offset.x = -FOLLOWING_OFFSET;
			currentDirection = RIGHT;
			nextAnimation = WALK_LEFT;
			this->setScale(sf::Vector2f(-FOLLOWER_SCALE, FOLLOWER_SCALE));
		}
		else if (pathX < -FOLLOWING_OFFSET) {
			offset.x = FOLLOWING_OFFSET;
			currentDirection = LEFT;
			nextAnimation = WALK_LEFT;
			this->setScale(sf::Vector2f(FOLLOWER_SCALE, FOLLOWER_SCALE));
		}

		if (pathY > FOLLOWING_OFFSET) {
			currentDirection = DOWN;
			if (speed < 0) speed = -speed;
			offset.y = -FOLLOWING_OFFSET;
			nextAnimation = WALK_DOWN;
		}
		else if (pathY < -FOLLOWING_OFFSET) {
			currentDirection = UP;
			if (speed > 0) speed = -speed;
			offset.y = FOLLOWING_OFFSET;
			nextAnimation = WALK_UP;
		}
	}
	else {
		isMoving = false;
		currentDirection = STILL;
		StopCurrentAnimation();
	}

	if (currentDirection != nextDirection)
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

	if (isMoving)
	{
		const float dir = atan((player->getPosition().x + offset.x - this->getPosition().x) / (player->getPosition().y + offset.y - this->getPosition().y));
		this->move(speed * d * sin(dir), speed * d * cos(dir));
	}
	
	count += d;
}
