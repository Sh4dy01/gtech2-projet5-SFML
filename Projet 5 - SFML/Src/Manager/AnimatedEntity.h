#pragma once

#include "Entity.h"

class AnimatedEntity : public Entity
{

public:

    AnimatedEntity(std::vector<sf::IntRect>, sf::String);
    void nextAnimation(void);

protected:

    size_t count;
    std::vector<sf::IntRect> animationPos;

};