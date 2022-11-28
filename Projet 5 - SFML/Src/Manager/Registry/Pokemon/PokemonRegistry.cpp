#include "PokemonRegistry.h"

#include "AttackRegistry.h"



static const Attack* Bulbasaur_Attacks[] =
{
	&AttackRegistry::VINE_WHIP,
	&AttackRegistry::TACKLE
};

static const Attack* Charmander_Attacks[] =
{
	&AttackRegistry::EMBER,
	&AttackRegistry::SCRATCH
};

static const Attack* Squirtle_Attacks[] =
{
	&AttackRegistry::WATER_GUN,
	&AttackRegistry::TACKLE
};

static const Attack* Rattata_Attacks[] =
{
	&AttackRegistry::TACKLE,
	&AttackRegistry::QUICK_ATTACK
};

static const Attack* Pikachu_Attacks[] =
{
	&AttackRegistry::THUNDER_SHOCK,
	&AttackRegistry::QUICK_ATTACK
};

static const Attack* Sandshrew_Attacks[] =
{
	&AttackRegistry::ROLLOUT,
	&AttackRegistry::SCRATCH
};

static const Attack* Abra_Attacks[] =
{
	&AttackRegistry::CONFUSION
};

static const Attack* Magikarp_Attacks[] =
{
	&AttackRegistry::SPLASH,
	&AttackRegistry::TACKLE
};

static const Attack* Arceus_Attacks[] =
{
	&AttackRegistry::JUDGMENT,
	&AttackRegistry::HYPER_BEAM
};



const PokedexEntry PokemonRegistry::pokemons[] =
{
	PokedexEntry(1,   "BULBASAUR",  Element::GRASS,    2, Bulbasaur_Attacks),
	PokedexEntry(4,   "CHARMANDER", Element::FIRE,     2, Charmander_Attacks),
	PokedexEntry(7,   "SQUIRTLE",   Element::WATER,    2, Squirtle_Attacks),
	PokedexEntry(19,  "RATTATA",    Element::NATURE,   2, Rattata_Attacks),
	PokedexEntry(25,  "PIKACHU",    Element::ELECTRIC, 2, Pikachu_Attacks),
	PokedexEntry(27,  "SANDSHREW",  Element::GROUND,   2, Sandshrew_Attacks),
	PokedexEntry(63,  "ABRA",       Element::PSYCHIC,  1, Abra_Attacks),
	PokedexEntry(129, "MAGIKARP",   Element::WATER,    2, Magikarp_Attacks),
	PokedexEntry(493, "ARCEUS",     Element::NORMAL,   2, Arceus_Attacks),
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
