#pragma once
#include "Manager/AnimatedEntity.h"
#include "Manager/PlayerController.h"
#include "PokemonRegistry.h"

class PokemonWorld : public AnimatedEntity {

public:
	
	PokemonWorld(int pokedexNumber);

	bool IsPlayerDetected(Player* player);
	virtual void Move(double d) override;
	virtual void StopCurrentAnimation(void) override;

protected:
	
	const PokedexEntry* pokemon;
};