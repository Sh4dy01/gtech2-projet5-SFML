#pragma once

#include "Manager/SpriteConfig.h"
#include "AnimatedEntity.h"

class Follower;

class Player : public AnimatedEntity {

public:

	Player();
	void CheckInputs(double deltaTime);
	void CheckLateralDirections(double deltaTime);
	
	void MoveFollower(double deltaTime);
	void SpawnFollower(int pokedexNumber);

	Follower* GetFollower() { return follower; };
	std::vector<int>& GetPokemonsCaught() { return pokemonsCaught; };
	int getSelectedPokemon() const { return pokemonsCaught.empty() ? -1 : pokemonsCaught[pokemonSelected]; }
	int GetSpeed() { return this->speed; };

	bool IsFollowerSpawned() { return this->isFollowerSpawned; };

	void SetPokemonsCaught(std::vector<int> pokemons) { pokemonsCaught = pokemons; };

private:

	double keyPressed;
	Follower* follower;
	bool isFollowerSpawned;

	int pokemonSelected;
	std::vector<int> pokemonsCaught;
};