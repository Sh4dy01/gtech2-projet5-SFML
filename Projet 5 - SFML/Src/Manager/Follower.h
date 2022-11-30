#pragma once

#include "Registry/Pokemon/PokemonWorld.h"

class Follower : public PokemonWorld {

public:

	Follower(Player*);
	void ChangeFollower(int pokedexNumber);
	virtual void Move(double d) override;
	//virtual void Move(double d) override;

private:

	Player* player;
};