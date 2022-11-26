#include "PokemonRegistry.h"


const PokedexEntry PokemonRegistry::pokemons[] =
{
	PokedexEntry(1,   "BULBASAUR",  Element::GRASS),
	PokedexEntry(4,   "CHARMANDER", Element::FIRE),
	PokedexEntry(7,   "SQUIRTLE",   Element::WATER),
	PokedexEntry(19,  "RATTATA",    Element::NATURE),
	PokedexEntry(25,  "PIKACHU",    Element::ELECTRIC),
	PokedexEntry(27,  "SANDSHREW",  Element::GROUND),
	PokedexEntry(63,  "ABRA",       Element::PSYCHIC),
	PokedexEntry(129, "MAGIKARP",   Element::WATER),
	PokedexEntry(493, "ARCEUS",     Element::NORMAL),
};


// Get Pokemon by Pokedex number.
// Since the list of Pokemons is sorted, we can run a simple binary search.
static int bin_search(const PokedexEntry* list, int begin, int end, int value);

const PokedexEntry* PokemonRegistry::getPokemonByPokedexNumber(int pokedexID)
{
	int elemCount = (sizeof(PokemonRegistry::pokemons)) / (sizeof(PokedexEntry));

	int id = bin_search(PokemonRegistry::pokemons, 0, elemCount, pokedexID);
	return (id == -1) ? 0 : &PokemonRegistry::pokemons[id];
}



// Binary search using iterative approach (which gives O(1) in space complexity, while
// recursive approach gives O(n)).
static int bin_search(const PokedexEntry* list, int begin, int end, int value)
{
	int avg;
	const PokedexEntry* e;

	while (begin < end)
	{
		avg = (begin + end) / 2;
		e = &list[avg];

		if (e->getPokedexID() < value) begin = avg + 1;
		else if (e->getPokedexID() > value) end = avg;
		else return avg;
	}

	return -1;
}
