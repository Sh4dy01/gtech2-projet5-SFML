#pragma once

#include "Manager/SpriteConfig.h"
#include "Entity.h"
#include "Common/Point2.h"

class Player : public Entity {

public:
	Player();
	void MovePLayer(sf::Vector2f newPos);

private:
	
	float speed = 1.0f;
};