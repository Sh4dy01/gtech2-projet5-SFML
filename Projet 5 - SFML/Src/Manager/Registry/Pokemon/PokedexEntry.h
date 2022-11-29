#pragma once

class Attack;


	/// List of all possible Pokemon elements.
enum Element
{
	NORMAL,
	NATURE,
	FIRE,
	WATER,
	GRASS,
	ELECTRIC,
	ICE,
	FIGHTING,
	POISON,
	GROUND,
	FLYING,
	PSYCHIC,
	BUG,
	ROCK,
	GHOST,
	DRAGON,
	DARK,
	STEEL
};


	/// An entry in the Pokemon registry.
	/// Each entry corresponds to a specific evolution of a Pokemon (i.e. a specific Pokedex number).
class PokedexEntry
{
public:

	PokedexEntry(int pokedexID, const char* name, Element e, int numAttacks, const Attack** attacks);

	int getPokedexID() const { return pokedexID; }

	const char* getName() const { return name; }
	Element getElement() const { return element; }



private:

	int pokedexID;

	const char* name;
	Element element;

	int numAttacks;
	const Attack** attacks;
};
