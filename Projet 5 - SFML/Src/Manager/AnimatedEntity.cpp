#include "AnimatedEntity.h"
#include "Game.h"
#include "Manager/SpriteConfig.h"
#include <iostream>

AnimatedEntity::AnimatedEntity(std::vector<std::vector<sf::IntRect>> animations, sf::String name, bool isPokemon) : Entity(name, isPokemon)
{
	this->currentAnimation = WALK_DOWN;
	this->nextAnimation = WALK_DOWN;

	this->currentDirection = STILL;
	this->nextDirection = STILL;
	this->isMoving = false;

    this->count = 0;
    this->pos = 0;
    this->animations = animations;
}

void AnimatedEntity::Initialize(float scale, sf::Vector2i spawn)
{
    this->setScale(sf::Vector2f(scale, scale));
    this->SetSpawn(sf::Vector2f(spawn));
    this->SetSprite();

	switch (currentDirection)
	{
	case LEFT:
		currentAnimation = WALK_LEFT;
		break;
	case UP:
		currentAnimation = WALK_UP;
		break;
	case RIGHT:
		currentAnimation = WALK_LEFT;
		this->setScale(-1.0f, 1.0f);
		break;
	case DOWN:
		currentAnimation = WALK_DOWN;
		break;
	default:
		break;
	}

	this->setTextureRect(this->animations[currentAnimation][this->pos]);
	this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

void AnimatedEntity::Move(double d) {
	sf::Vector2i pos = sf::Vector2i(this->getPosition().x / SPRITE_SIZE, this->getPosition().y / SPRITE_SIZE);

	if (IsSnappedToGrid() && currentDirection != nextDirection)
	{
		currentDirection = nextDirection;
		int x = int(getPosition().x);
		int y = int(getPosition().y);

		this->setPosition(x, y);
	}
	if (currentAnimation != nextAnimation)
	{
		currentAnimation = nextAnimation;
	}

	switch (currentDirection)
	{
	case STILL:
		this->move(0.0f, 0.0f);
		StopCurrentAnimation();
		isMoving = false;
		break;

	case LEFT:
		this->move(-speed * d, 0.0f);
		nextAnimation = WALK_LEFT;
		isMoving = true;
		break;

	case UP:
		this->move(0.0f, -speed * d);
		nextAnimation = WALK_UP;
		isMoving = true;
		break;

	case RIGHT:
		this->move(speed * d, 0.0f);
		nextAnimation = WALK_RIGHT;
		isMoving = true;
		break;

	case DOWN:
		this->move(0.0f, speed * d);
		nextAnimation = WALK_DOWN;
		isMoving = true;
		break;
	}

	if (count >= 0.2)
	{
		NextAnimationFrame();
		count = 0;
	}

	count += d;
}

bool AnimatedEntity::IsSnappedToGrid()
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

void AnimatedEntity::NextAnimationFrame(void)
{
    if (isMoving)
    {
        this->pos++;

        if (this->pos >= this->animations[currentAnimation].size())
            this->pos = 0;

        this->setTextureRect(animations[this->currentAnimation][this->pos]);
    }
}


void AnimatedEntity::StopCurrentAnimation() {
    this->pos = 0;
    switch (currentAnimation)
    {
    case WALK_DOWN:
        this->currentAnimation = STAND_DOWN;
        break; 
    case WALK_UP:
        this->currentAnimation = STAND_UP;
        break;
    default:
        break;
    }

    this->setTextureRect(animations[this->currentAnimation][this->pos]);
}