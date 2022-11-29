#pragma once

#include "Entity.h"

enum animationType
{
    WALK_DOWN,
    WALK_UP,
    WALK_LEFT,
    WALK_RIGHT,
    STAND_UP,
    STAND_DOWN
};

enum direction
{
    STILL,
    LEFT,
    UP,
    RIGHT,
    DOWN
};

class AnimatedEntity : public Entity
{

public:

    AnimatedEntity(std::vector<std::vector<sf::IntRect>>, sf::String, bool isPokemon);
    virtual void Initialize(int scale, sf::Vector2i spawn);

    virtual void Move(double d);
    bool IsSnappedToGrid();
    void SetDirection(direction dir) { nextDirection = dir; };
    direction GetCurrentDirection() { return currentDirection; };

    void NextAnimationFrame(void);
    virtual void StopCurrentAnimation(void);

protected:

    bool isMoving;
    
    double count;
    int pos;

    direction nextDirection;
    direction currentDirection;

    animationType currentAnimation;
    animationType nextAnimation;
    std::vector<std::vector<sf::IntRect>> animations;
};