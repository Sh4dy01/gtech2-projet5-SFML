#include "SFML/Window/Keyboard.hpp"
#include "PlayerController.h"
#include "Manager/SpriteConfig.h"
#include <iostream>

Player::Player() : AnimatedEntity(PLAYER_ANIMATION, "Dave", false)
{
	speed = 50.0f;
	follower = new Follower(this);
}

void Player::CheckAllDirections(double d) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) //Move Up
		this->SetDirection(UP);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
		this->SetDirection(DOWN);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
		this->SetDirection(RIGHT);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) //Move Left
		this->SetDirection(LEFT);
	else
		this->SetDirection(STILL);

	this->Move(d);
}

void Player::CheckLateralDirections(double d) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->SetDirection(RIGHT);
		follower->SetDirection(RIGHT);
	} //Move Right
		

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		this->SetDirection(LEFT);
		follower->SetDirection(LEFT);
	} //Move Left
		
	else {
		this->SetDirection(STILL);
		follower->SetDirection(STILL);
	}

	this->Move(d);

	if (follower)
	{
		follower->Move(d);
	}
}

void Player::SpawnFollower()
{
	sf::Vector2i playerPos = sf::Vector2i(this->getPosition().x/SPRITE_SIZE, this->getPosition().y / SPRITE_SIZE);

	switch (this->GetCurrentDirection())
	{
	case LEFT:
		playerPos.x++;
		break;
	case RIGHT:
		playerPos.x--;
		break;
	case UP:
		playerPos.y++;
		break;
	case DOWN:
		playerPos.y--;
	default:
		playerPos.x--;
		break;
	}

	follower->Initialize(1, playerPos);
}
