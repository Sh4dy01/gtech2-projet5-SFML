#pragma once
#include "AnimatedEntity.h"

class PokemonWorld : public AnimatedEntity {

public:
	
	PokemonWorld(std::vector<std::vector<sf::IntRect>> animations, sf::String name);
	virtual void Move(double d) override;
	virtual void StopCurrentAnimation(void) override;

private:

};