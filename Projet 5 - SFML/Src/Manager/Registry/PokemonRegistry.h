#pragma once

#include "PokedexEntry.h"


class PokemonRegistry
{
public:

	static const PokedexEntry* getPokemons() { return pokemons; }
	static const PokedexEntry* getPokemonByPokedexNumber(int pokedexID);

private:

	static const PokedexEntry pokemons[];
};
