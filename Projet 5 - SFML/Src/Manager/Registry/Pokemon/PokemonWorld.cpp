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

	float distX = (player->getPosition().x - this->getPosition().x) / SPRITE_SIZE;
	float distY = (player->getPosition().y - this->getPosition().y) / SPRITE_SIZE;
	
	if (name == "BULBASAUR")
	{
		std::cout << name << " : " << distX << ", " << distY << std::endl;
	}

	switch (currentDirection)
	{
	case LEFT:
		if (distX <= 0 && distY <= 0.5 && distY >= -0.5 && abs(distX) <= range)
			return true;
		break;

	case UP:
		if (distY <= 0 && distX <= 0.5 && distX >= -0.5 && abs(distY) <= range)
			return true;
		break;

	case RIGHT:
		if (distX >= 0 && distY <= 0.5 && distY >= -0.5 && abs(distX) <= range)
			return true;
		break;

	case DOWN:
		if (distY >= 0 && distX <= 0.5 && distX >= -0.5 && abs(distY) <= range)
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
