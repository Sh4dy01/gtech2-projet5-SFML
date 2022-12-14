#pragma once

#include "Registry/Pokemon/PokemonWorld.h"
#define FOLLOWER_SCALE 0.5

class Follower : public PokemonWorld {

public:

	Follower(Player*, int pokedexNumber);
	void ChangeFollower(int pokedexNumber);
	void SetToPlayerPosition();
	virtual void Move(double d) override;

private:

	Player* player;
};