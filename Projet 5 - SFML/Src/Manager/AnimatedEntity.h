#pragma once

#include "Entity.h"

enum animationType
{
    WALK_DOWN = 0,
    WALK_UP = 1,
    WALK_LEFT = 2,
    WALK_RIGHT = 3,
    STAND_UP = 4,
    STAND_DOWN = 5
};

class AnimatedEntity : public Entity
{

public:

    AnimatedEntity(std::vector<std::vector<sf::IntRect>>, sf::String);
    void Initialize(int scale, sf::Vector2i spawn);
    void NextAnimationFrame(void);
    void StopCurrentAnimation(void);

protected:

    bool isMoving;
    
    double count;
    int pos;

    animationType currentAnimation;
    animationType nextAnimation;
    std::vector<std::vector<sf::IntRect>> animations;
};