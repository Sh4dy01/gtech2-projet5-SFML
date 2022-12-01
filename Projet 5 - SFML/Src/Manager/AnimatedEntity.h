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

    AnimatedEntity(std::vector<std::vector<sf::IntRect>>, std::string, bool isPokemon);
    virtual void Initialize(float scale, sf::Vector2i spawn);

    virtual void Move(double d);
    bool IsSnappedToGrid();
    bool IsThereACollision(void);

    void NextAnimationFrame(void);
    virtual void StopCurrentAnimation(void);

    direction GetCurrentDirection() { return currentDirection; };
    bool CanMove() { return canMove ; }

    void SetDirection(direction dir) { nextDirection = dir; };
    void SetCurrentDirection(direction dir) { currentDirection = dir; };
    void SetMovementAbility(bool canMove) { this->canMove = canMove; }
protected:

    bool isMoving;
    bool canMove;
    
    double count;
    int pos;

    direction nextDirection;
    direction currentDirection;

    animationType currentAnimation;
    animationType nextAnimation;
    std::vector<std::vector<sf::IntRect>> animations;
};