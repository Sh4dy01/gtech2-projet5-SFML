#include "Follower.h"
#include "Configs/Pokemon/Miaouss.h"
#include "PlayerController.h"
#include <cmath>

#define FOLLOWING_OFFSET  1.2

Follower::Follower(Player* player) : PokemonWorld(MIAOUSS_ANIMATION, "miaouss")
{
	following = player;
}

void Follower::ChangeFollower()
{

}

void Follower::Move(double d)
{
	const float dir = atan((following->getPosition().x - this->getPosition().x) / (following->getPosition().y - this->getPosition().y));

	switch (currentDirection)
	{
	case STILL:
		StopCurrentAnimation();
		isMoving = false;
		break;
	case LEFT:
		nextAnimation = WALK_LEFT;
		this->setScale(sf::Vector2f(1.0f, 1.0f));
		isMoving = true;
		break;
	case UP:
		nextAnimation = WALK_UP;
		isMoving = true;
		break;
	case RIGHT:
		nextAnimation = WALK_LEFT;
		isMoving = true;
		this->setScale(sf::Vector2f(-1.0f, 1.0f));
		break;
	case DOWN:
		nextAnimation = WALK_DOWN;
		isMoving = true;
		break;
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
		this->move(speed * sin(dir), speed * cos(dir));
	}

	count += d;
}
