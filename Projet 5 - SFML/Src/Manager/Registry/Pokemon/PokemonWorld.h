#pragma once
#include "Manager/AnimatedEntity.h"
#include "PokemonRegistry.h"

class PokemonWorld : public AnimatedEntity {

public:
	
	PokemonWorld(int pokedexNumber);
	virtual void Move(double d) override;
	virtual void StopCurrentAnimation(void) override;

protected:
	
	const PokedexEntry* pokemon;
};