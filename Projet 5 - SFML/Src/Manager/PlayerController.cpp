#include "SFML/Window/Keyboard.hpp"
#include "PlayerController.h"
#include <iostream>
#include "Manager/SpriteConfig.h"

Player::Player() : Entity(PLAYER_NAME)
{
	currentDirection = STILL;
	nextDirection = STILL;
	speed = 1.0f;
}

bool Player::IsChangedDir()
{
	if (this->IsSnappedToGrid() && currentDirection != nextDirection)
	{
		currentDirection = nextDirection;
		return true;
	}

	return false;
}

void Player::CheckDirection() {

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

	Move();
}

void Player::Move() {
	switch (currentDirection)
	{
	case STILL:
		this->move(0.0f, 0.0f);
		break;
	case LEFT:
		this->move(-speed, 0.0f);
		break;
	case UP:
		this->move(0.0f, -speed);
		break;
	case RIGHT:
		this->move(speed, 0.0f);
		break;
	case DOWN:
		this->move(0.0f, speed);
		break;
	}

	if (this->IsSnappedToGrid() && currentDirection != nextDirection)
	{
		currentDirection = nextDirection;
	}
}

bool Player::IsSnappedToGrid()
{
	if (int(this->getPosition().x) % (SPRITE_SIZE * BASE_SCALE_FACTOR) == 0 &&
		int(this->getPosition().y) % (SPRITE_SIZE * BASE_SCALE_FACTOR) == 0)
	{
		return true;
	}
	else {
		return false;
	}
}
