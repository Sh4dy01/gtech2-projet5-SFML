#pragma once

#include "Manager/State/State.h"
#include "Manager/PlayerController.h"
#include "Map/Map.h"

class PokemonWorld;


class StateLevel : public State
{
public:

	StateLevel();

	void StartIntro();

	virtual void enter(sf::Vector2i) override;
	virtual void leave() override;
	virtual void update(double deltaTime) override;
	virtual void render(sf::RenderWindow& window) override;

private:

	bool IsIntro;
	double count;
	Entity meteor;

	std::vector<Tile> levelTiles;
	std::vector<PokemonWorld*> pokemons;

	sf::View camera;
	Map currentMap;
	Player player;

};
