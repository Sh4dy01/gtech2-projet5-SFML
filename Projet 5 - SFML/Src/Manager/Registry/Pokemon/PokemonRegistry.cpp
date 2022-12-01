#include "PokemonRegistry.h"
#include "AttackRegistry.h"
#include "PokemonAnimationsRegistry.h"



static const char* element_strings[] =
{
	"NORMAL",
	"FIRE",
	"WATER",
	"GRASS",
	"ELECTRIC",
	"ICE",
	"FIGHTING",
	"POISON",
	"GROUND",
	"FLYING",
	"PSYCHIC",
	"BUG",
	"ROCK",
	"GHOST",
	"DRAGON",
	"DARK",
	"STEEL"
};



static const Attack* Dave_Attacks[] =
{
	&AttackRegistry::PUNCH
};

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

static const Attack* Meowth_Attacks[] =
{
	&AttackRegistry::SCRATCH,
	&AttackRegistry::GROWL
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
	PokedexEntry(0,   "DAVE",       Element::NORMAL,   100, 1, Dave_Attacks,       { } ),
	PokedexEntry(1,   "BULBASAUR",  Element::GRASS,    45,  2, Bulbasaur_Attacks,  BULBASAUR_ANIMATIONS),
	PokedexEntry(4,   "CHARMANDER", Element::FIRE,     39,  2, Charmander_Attacks, CHARMANDER_ANIMATIONS),
	PokedexEntry(7,   "SQUIRTLE",   Element::WATER,    44,  2, Squirtle_Attacks,   SQUIRTLE_ANIMATIONS),
	PokedexEntry(19,  "RATTATA",    Element::NORMAL,   30,  2, Rattata_Attacks,    RATTATA_ANIMATIONS),
	PokedexEntry(25,  "PIKACHU",    Element::ELECTRIC, 35,  2, Pikachu_Attacks,    PIKACHU_ANIMATIONS),
	PokedexEntry(27,  "SANDSHREW",  Element::GROUND,   50,  2, Sandshrew_Attacks,  SANDSHREW_ANIMATIONS),
	PokedexEntry(52,  "MEOWTH",	    Element::NORMAL,   40,  2, Meowth_Attacks,     MEOWTH_ANIMATIONS),
	PokedexEntry(63,  "ABRA",       Element::PSYCHIC,  25,  1, Abra_Attacks,       ABRA_ANIMATIONS),
	PokedexEntry(129, "MAGIKARP",   Element::WATER,    20,  2, Magikarp_Attacks,   MAGIKARP_ANIMATIONS),
	PokedexEntry(493, "ARCEUS",     Element::NORMAL,   120, 2, Arceus_Attacks,     ARCEUS_ANIMATIONS),
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

const char* PokemonRegistry::getElementName(Element e)
{
	return element_strings[e];
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
