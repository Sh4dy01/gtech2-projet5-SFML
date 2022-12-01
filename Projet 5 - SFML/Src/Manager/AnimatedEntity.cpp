#include "AnimatedEntity.h"
#include "Game.h"
#include "Manager/SpriteConfig.h"
#include <iostream>

AnimatedEntity::AnimatedEntity(std::vector<std::vector<sf::IntRect>> animations, std::string name, bool isPokemon) : Entity(name, isPokemon)
{
	this->currentAnimation = WALK_DOWN;
	this->canMove = true;

	this->currentDirection = STILL;
	this->isMoving = false;

    this->count = 0;
    this->pos = 0;
    this->animations = animations;
}

void AnimatedEntity::Initialize(float scale, sf::Vector2i spawn)
{
	this->currentDirection = STILL;

	this->scale = scale;
    this->setScale(sf::Vector2f(scale, scale));
    this->SetSpawn(sf::Vector2f(spawn));
    this->SetSprite();

	

	this->setTextureRect(this->animations[currentAnimation][this->pos]);
	this->setOrigin(this->getLocalBounds().width / 2, this->getLocalBounds().height / 2);
}

void AnimatedEntity::Move(double d) {
	sf::Vector2i pos = sf::Vector2i(this->getPosition().x / SPRITE_SIZE, this->getPosition().y / SPRITE_SIZE);

	if (IsSnappedToGrid() && currentDirection != nextDirection)
	{
		currentDirection = nextDirection;
		switch (currentDirection)
		{
		case LEFT:
			this->setScale(scale, scale);
			break;
		case RIGHT:
			this->setScale(-scale, scale);
			break;
		}

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
		nextAnimation = WALK_LEFT;
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
	case WALK_UP:
		this->currentAnimation = STAND_UP;
		break;
	case WALK_DOWN:
		this->currentAnimation = STAND_DOWN;
		break;
	}
    this->setTextureRect(animations[this->currentAnimation][this->pos]);
}

bool AnimatedEntity::IsThereACollision() {
	return Game::getInstance().getMap().thereIsCollision(getPosition().x / SPRITE_SIZE - 1, getPosition().y / SPRITE_SIZE - 1, currentDirection);
}

void AnimatedEntity::SetCurrentDirection(direction dir) {
	this->pos = 0;
	this->currentDirection = dir;
	this->nextDirection = currentDirection;

	switch (currentDirection)
	{
	case LEFT:
		currentAnimation = WALK_LEFT;
		this->setScale(scale, scale);
		break;
	case UP:
		currentAnimation = WALK_UP;
		break;
	case RIGHT:
		currentAnimation = WALK_LEFT;
		this->setScale(-scale, scale);
		break;
	case DOWN:
		currentAnimation = WALK_DOWN;
		break;
	default:
		break;
	}
	this->nextAnimation = currentAnimation;

	this->setTextureRect(animations[this->currentAnimation][this->pos]);
}

void AnimatedEntity::SetMovementAbility(bool canMove) {
	StopCurrentAnimation();
	this->canMove = canMove;
}