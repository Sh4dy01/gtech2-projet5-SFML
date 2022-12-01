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

		if (range >= 5)
			break;

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

void PokemonWorld::StopCurrentAnimation(void)
{
	this->pos = 0;
	this->setTextureRect(animations[this->currentAnimation][this->pos]);
}
