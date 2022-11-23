#include "PlayerController.h"

Player::Player(sf::Vector2f spawn) : Entity(PLAYER_NAME, spawn)
{
}

void Player::MovePLayer(sf::Vector2f newPos)
{
	pos += newPos;
}
