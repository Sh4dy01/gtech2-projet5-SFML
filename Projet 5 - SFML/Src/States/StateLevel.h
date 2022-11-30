#pragma once

#include "Manager/State/State.h"
#include "Manager/PlayerController.h"
#include "Map/Map.h"

class PokemonWorld;


class StateLevel : public State
{
public:

	StateLevel();

	virtual void enter() override;
	virtual void leave() override;
	virtual void update(double deltaTime) override;
	virtual void render(sf::RenderWindow& window) override;

private:

	std::vector<Tile> levelTiles;
	std::vector<PokemonWorld*> pokemons;

	sf::View camera;
	Map currentMap;
	Player player;

};
