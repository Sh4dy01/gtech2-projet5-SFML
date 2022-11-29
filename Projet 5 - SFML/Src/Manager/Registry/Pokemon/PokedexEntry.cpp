#include "PokedexEntry.h"


PokedexEntry::PokedexEntry(int pokedexID, const char* name, Element e, int numAttacks, const Attack** attacks)
	: pokedexID(pokedexID), name(name), element(e), numAttacks(numAttacks), attacks(attacks)
{

}
