#include "AnimatedEntity.h"
#include "Manager/SpriteConfig.h"
#include <iostream>

AnimatedEntity::AnimatedEntity(std::vector<std::vector<sf::IntRect>> animations, sf::String name) : Entity(name)
{
    currentAnimation = WALK_DOWN;
    nextAnimation = WALK_DOWN;

    this->count = 0;
    this->pos = 0;
    this->animations = animations;

    if (animations.size() <= 0)
        throw;

    this->setTextureRect(this->animations[currentAnimation][this->pos]);
}

void AnimatedEntity::Initialize(int scale, sf::Vector2i spawn)
{
    this->setScale(sf::Vector2f(BASE_SCALE_FACTOR + scale, BASE_SCALE_FACTOR + scale));
    this->SetSpawn(sf::Vector2f(spawn));
    this->SetSprite();
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