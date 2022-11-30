#include "SFML/Window/Keyboard.hpp"
#include "PlayerController.h"
#include "Manager/SpriteConfig.h"
#include <iostream>
#include "Game.h"

Player::Player() : AnimatedEntity(PLAYER_ANIMATION, "Dave", false)
{
	speed = 50.0f;
	follower = new Follower(this);
}

void Player::CheckAllDirections(double d) {

	sf::Vector2f position= this->getPosition();

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) //Move Up
	{
		if (Game::getInstance().currentMap->thereIsCollision( position.x, position.y - 1 ))
			SetDirection(UP);
		else
			SetDirection(STILL);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) //Move Down
	{
		if (Game::getInstance().currentMap->thereIsCollision(position.x, position.y + 1))
			SetDirection(DOWN);
		else
			SetDirection(STILL);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) //Move Right
	{
		if (Game::getInstance().currentMap->thereIsCollision(position.x + 1, position.y))
			SetDirection(RIGHT);
		else
			SetDirection(STILL);
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) //Move Left
	{
		if (Game::getInstance().currentMap->thereIsCollision(position.x - 1, position.y))
			SetDirection(LEFT);
		else
			SetDirection(STILL);
	}

	

	else
		SetDirection(STILL);

	this->Move(d);
	MoveFollower(d);
}

void Player::CheckLateralDirections(double d) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		this->SetDirection(RIGHT);
	} //Move Right
		

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		this->SetDirection(LEFT);
	} //Move Left

	else {
		this->SetDirection(STILL);
	}

	this->Move(d);
	MoveFollower(d);
}

void Player::MoveFollower(double deltaTime)
{
	if (follower)
	{
		follower->Move(deltaTime);
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
