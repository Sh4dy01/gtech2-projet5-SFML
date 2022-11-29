#pragma once

#include "PokemonWorld.h"

class Player;

class Follower : public PokemonWorld {

public:

	Follower(Player*);
	void ChangeFollower();
	virtual void Move(double d) override;
	//virtual void Move(double d) override;

private:

	Player* player;
};