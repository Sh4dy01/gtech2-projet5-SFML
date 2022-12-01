#include "PokedexEntry.h"


PokedexEntry::PokedexEntry(int pokedexID, const char* name, Element e, int maxHealth, int numAttacks, const Attack** attacks, std::vector<std::vector<sf::IntRect>> animations)
	: pokedexID(pokedexID), name(name), element(e), maxHealth(maxHealth)
	, numAttacks(numAttacks), attacks(attacks), animations(animations)
{

}

std::string PokedexEntry::getSpriteFightFilename() const
{
	std::string f = name;
	for (char& c : f) c = tolower(c);

	f += "_fight.png";
	return f;
}

std::string PokedexEntry::getSpriteOpponentFilename() const
{
	std::string f = name;
	for (char& c : f) c = tolower(c);

	f += "_opponent.png";
	return f;
}
