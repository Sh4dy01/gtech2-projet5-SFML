#pragma once

#include "Manager/State/State.h"
#include "Manager/PlayerController.h"
#include "Map/Map.h"

class PokemonWorld;


class StateLevel : public State
{
public:

	StateLevel();
	StateLevel(sf::Vector2i);

	void StartIntro();

	virtual void enter() override;
	virtual void leave() override;
	virtual void update(double deltaTime) override;
	virtual void render(sf::RenderWindow& window) override;

	void SetIsIntroPlayed(bool b) { IsIntroPlayed = b; };
	Player& getPlayer();
	bool GetIsIntroPlayed() { return IsIntroPlayed; };

private:

	bool IsIntro;
	bool IsIntroPlayed;
	double count;
	Entity meteor;

	std::vector<Tile> levelTiles;
	std::vector<PokemonWorld*> pokemons;

	sf::View camera;
	Map currentMap;
	Player player;

	sf::Vector2i playerPos;

};
