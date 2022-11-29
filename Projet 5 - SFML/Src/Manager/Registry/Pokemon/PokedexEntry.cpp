#include "PokedexEntry.h"


PokedexEntry::PokedexEntry(int pokedexID, const char* name, Element e, int numAttacks, const Attack** attacks, std::vector<std::vector<sf::IntRect>> animations)
	: pokedexID(pokedexID), name(name), element(e), numAttacks(numAttacks), attacks(attacks), animations(animations)
{

}
