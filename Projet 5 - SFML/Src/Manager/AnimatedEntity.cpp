#include "AnimatedEntity.h"


AnimatedEntity::AnimatedEntity(std::vector<sf::IntRect> animationPos, sf::String name) : Entity(name)
{
    this->count = 0;
    this->animationPos = animationPos;

    if (animationPos.size() <= 0)
        throw;

    this->setTextureRect(this->animationPos[this->count]);
}

void AnimatedEntity::nextAnimation(void)
{
    this->count++;

    if (this->count >= this->animationPos.size())
        this->count = 0;

    this->setTextureRect(animationPos[this->count]);
}