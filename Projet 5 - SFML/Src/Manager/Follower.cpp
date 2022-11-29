#include "Follower.h"
#include "Configs/Pokemon/Miaouss.h"
#include "PlayerController.h"
#include <cmath>

#define FOLLOWING_OFFSET  (1.5*SPRITE_SIZE)

Follower::Follower(Player* player) : PokemonWorld(MIAOUSS_ANIMATION, "miaouss"), player(player)
{
	speed = player->GetSpeed()*0.95;
	currentDirection = STILL;
	this->setScale(sf::Vector2f(-1.0f, 1.0f));
}

void Follower::ChangeFollower()
{

}

void Follower::Move(double d)
{
	sf::Vector2i offset;
	float pathX = player->getPosition().x - this->getPosition().x;
	float pathY = player->getPosition().y - this->getPosition().y;

	if (pathX > FOLLOWING_OFFSET)
	{
		offset.x = -FOLLOWING_OFFSET;
		isMoving = true;
		currentDirection = RIGHT;
		nextAnimation = WALK_LEFT;
		this->setScale(sf::Vector2f(-1.0f, 1.0f));
	}
	else if (pathX < -FOLLOWING_OFFSET) {
		offset.x = FOLLOWING_OFFSET;
		isMoving = true;
		currentDirection = LEFT;
		nextAnimation = WALK_LEFT;
		this->setScale(sf::Vector2f(1.0f, 1.0f));
	}
	else if (pathY > FOLLOWING_OFFSET) {
		isMoving = true;
		currentDirection = DOWN;
		offset.y = -FOLLOWING_OFFSET;
		nextAnimation = WALK_DOWN;
	}
	else if (pathY < -FOLLOWING_OFFSET) {
		isMoving = true;
		currentDirection = UP;
		offset.y = FOLLOWING_OFFSET;
		nextAnimation = WALK_UP;
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