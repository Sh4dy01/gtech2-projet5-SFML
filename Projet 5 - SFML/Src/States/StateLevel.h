#pragma once

#include "Manager/State/State.h"
#include "Manager/PlayerController.h"

class PokemonWorld;


class StateLevel : public State
{
public:

	StateLevel();

	virtual void enter() override;
	virtual void update(double deltaTime) override;
	virtual void render(sf::RenderWindow& window) override;

private:

	sf::View camera;
	std::vector<PokemonWorld*> pokemons;
	Player player;

};
