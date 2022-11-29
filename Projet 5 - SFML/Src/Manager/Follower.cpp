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
	sf::Vector2i offset;

	switch (currentDirection)
	{
	case STILL:
		StopCurrentAnimation();
		isMoving = false;
		break;
	case LEFT:
		offset.x = FOLLOWING_OFFSET * SPRITE_SIZE;
		nextAnimation = WALK_LEFT;
		this->setScale(sf::Vector2f(1.0f, 1.0f));
		isMoving = true;
		break;
	case UP:
		offset.y = FOLLOWING_OFFSET * SPRITE_SIZE;
		nextAnimation = WALK_UP;
		isMoving = true;
		break;
	case RIGHT:
		offset.x = -FOLLOWING_OFFSET * SPRITE_SIZE;
		nextAnimation = WALK_LEFT;
		isMoving = true;
		this->setScale(sf::Vector2f(-1.0f, 1.0f));
		break;
	case DOWN:
		offset.y = -FOLLOWING_OFFSET * SPRITE_SIZE;
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
		const float dir = atan((following->getPosition().x + offset.x - this->getPosition().x) / (following->getPosition().y + offset.y - this->getPosition().y));
		this->move(speed * sin(dir), speed * cos(dir));
	}

	count += d;
}
