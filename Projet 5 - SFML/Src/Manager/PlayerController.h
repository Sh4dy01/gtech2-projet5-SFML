#pragma once

#include "Manager/SpriteConfig.h"
#include "AnimatedEntity.h"
#include "Follower.h"

class Player : public AnimatedEntity {

public:

	Player();
	void CheckAllDirections(double deltaTime);
	void CheckLateralDirections(double deltaTime);

	void SpawnFollower();

	Follower* GetFollower() { return follower; };
	int GetSpeed() { return this->speed; };

private:

	Follower* follower;
};