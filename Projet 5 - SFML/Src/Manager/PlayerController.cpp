#include "SFML/Window/Keyboard.hpp"
#include "PlayerController.h"
#include "Manager/SpriteConfig.h"
#include <iostream>

Player::Player() : AnimatedEntity(PLAYER_ANIMATION, "Dave")
{
	this->currentDirection = STILL;
	this->nextDirection = STILL;
	this->isMoving = false;

	speed = 0.5f;
}

void Player::CheckDirection(double d) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) //Move Up
		SetDirection(UP);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
		SetDirection(DOWN);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
		SetDirection(RIGHT);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) //Move Left
		SetDirection(LEFT);
	else
		SetDirection(STILL);

	Move(d);
}

void Player::Move(double d) {
	switch (currentDirection)
	{
	case STILL:
		this->move(0.0f, 0.0f);
		StopCurrentAnimation();
		isMoving = false;
		break;
	case LEFT:
		this->move(-speed, 0.0f);
		nextAnimation = WALK_LEFT;
		isMoving = true;
		break;
	case UP:
		this->move(0.0f, -speed);
		nextAnimation = WALK_UP;
		isMoving = true;
		break;
	case RIGHT:
		this->move(speed, 0.0f);
		nextAnimation = WALK_RIGHT;
		isMoving = true;

		break;
	case DOWN:
		this->move(0.0f, speed);
		nextAnimation = WALK_DOWN;
		isMoving = true;
		break;
	}

	if (this->IsSnappedToGrid() && currentDirection != nextDirection)
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

	count += d;
}

bool Player::IsSnappedToGrid()
{
	if (int(this->getPosition().x) % (SPRITE_SIZE) == 0 &&
		int(this->getPosition().y) % (SPRITE_SIZE) == 0)
	{
		return true;
	}
	else {
		return false;
	}
}
