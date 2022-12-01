#pragma once

#include "Manager/SpriteConfig.h"
#include "AnimatedEntity.h"

class Follower;

class Player : public AnimatedEntity {

public:

	Player();
	void CheckAllDirections(double deltaTime);
	void CheckLateralDirections(double deltaTime);
	
	void MoveFollower(double deltaTime);
	void SpawnFollower(int pokedexNumber);

	Follower* GetFollower() { return follower; };
	int GetSpeed() { return this->speed; };
	bool IsFollowerSpawned() { return this->isFollowerSpawned; };

private:

	double keyPressed;
	Follower* follower;
	bool isFollowerSpawned;
	int currentFollower;

	std::vector<int> pokemonsCaught;

};