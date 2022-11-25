#pragma once

#include "Manager/SpriteConfig.h"
#include "AnimatedEntity.h"
#include "Common/Point2.h"

enum direction
{
	STILL = 0,
	LEFT = 1,
	UP = 2,
	RIGHT = 3,
	DOWN = 4
};

class Player : public AnimatedEntity {

public:
	Player();
	void CheckAllDirections(double deltaTime);
	void CheckLateralDirections(double deltaTime);
	void Move(double deltaTime);

	void SetDirection(direction dir) { nextDirection = dir; };

	bool IsSnappedToGrid();

private:

	direction nextDirection;
	direction currentDirection;
};