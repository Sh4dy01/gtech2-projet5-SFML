#include "SFML/Window/Keyboard.hpp"
#include "PlayerController.h"
#include "Manager/SpriteConfig.h"
#include <iostream>
#include "Game.h"

#include "Follower.h"

Player::Player() : AnimatedEntity(PLAYER_ANIMATION, "Dave", false)
{
	speed = 50.0f;
	currentDirection = DOWN;
	currentAnimation = WALK_DOWN;
	currentFollower = 52;
	isFollowerSpawned = false;
}

void Player::CheckAllDirections(double d) {

	sf::Vector2i playerPos = sf::Vector2i(this->getPosition().x / SPRITE_SIZE, this->getPosition().y / SPRITE_SIZE);
	direction dir = STILL;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Z)) {//Move Up
		if (!Game::getInstance().getMap().thereIsCollision(playerPos.x-1, playerPos.y-1, UP))
			dir = UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {//Move Down
		if (!Game::getInstance().getMap().thereIsCollision(playerPos.x-1, playerPos.y-1, DOWN))
			dir = DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {//Move Right
		if (!Game::getInstance().getMap().thereIsCollision(playerPos.x-1, playerPos.y-1, RIGHT))
			dir = RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {//Move Left
		if (!Game::getInstance().getMap().thereIsCollision(playerPos.x-1, playerPos.y-1, LEFT))
			dir = LEFT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {//Spawn Follower
		if (currentFollower != 0 && !isFollowerSpawned && keyPressed >= 1)
		{
			SpawnFollower(currentFollower);
			follower->Show();
			isFollowerSpawned = true;
			keyPressed = 0;
		}
		else if (currentFollower != 0 && isFollowerSpawned && keyPressed >= 1) 
		{
			follower->Hide();
			isFollowerSpawned = false;
			keyPressed = 0;
		}
	}

	SetDirection(dir);

	this->Move(d);
	MoveFollower(d);

	if (keyPressed <= 2)
	{
		keyPressed += d;
	}
}

void Player::CheckLateralDirections(double d) {

	sf::Vector2i playerPos = sf::Vector2i(this->getPosition().x / SPRITE_SIZE, this->getPosition().y / SPRITE_SIZE);
	direction dir = STILL;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		if (!Game::getInstance().getMap().thereIsCollision(playerPos.x - 1, playerPos.y - 1, RIGHT))
			dir = RIGHT;
	}
		

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
		if (!Game::getInstance().getMap().thereIsCollision(playerPos.x - 1, playerPos.y - 1, LEFT))
			dir = LEFT;
	} 

	else {
		this->SetDirection(STILL);
	}

	SetDirection(dir);


	this->Move(d);
	MoveFollower(d);
}

void Player::MoveFollower(double deltaTime)
{
	if (follower)
	{
		follower->SetDirection(currentDirection);
		follower->Move(deltaTime);
	}
}

void Player::SpawnFollower(int pokedexNumber)
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

	follower = new Follower(this, pokedexNumber);
	follower->Initialize(FOLLOWER_SCALE, playerPos);
	State::getCurrentState()->addElement(follower);
}
