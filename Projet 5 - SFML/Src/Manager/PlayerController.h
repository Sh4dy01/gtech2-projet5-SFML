#pragma once

#include "Manager/SpriteConfig.h"
#include "Entity.h"
#include "Common/Point2.h"

enum direction
{
	STILL = 0,
	LEFT = 1,
	UP = 2,
	RIGHT = 3,
	DOWN = 4
};

class Player : public Entity {

public:
	Player();
	void CheckDirection();
	void Move();

	void SetDirection(direction dir) { nextDirection = dir; };

	bool IsChangedDir();
	bool IsSnappedToGrid();

private:

	direction nextDirection;
	direction currentDirection;
	float speed;
};