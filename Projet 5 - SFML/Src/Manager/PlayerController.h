#pragma once

#include "Manager/SpriteConfig.h"
#include "Entity.h"
#include "Common/Point2.h"

class Player : public Entity {

public:
	Player(sf::Vector2f);
	void MovePLayer(sf::Vector2f);

private:
	
	float speed = 1.0f;
};