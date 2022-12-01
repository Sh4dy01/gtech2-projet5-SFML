#pragma once
#include <vector>
#include "SFML/Graphics/Rect.hpp"

#include <string>

class Attack;


	/// List of all possible Pokemon elements.
enum Element
{
	NORMAL,
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

	PokedexEntry(int pokedexID, const char* name, Element e, int maxHealth, int numAttacks, const Attack** attacks, std::vector<std::vector<sf::IntRect>> animations);

	int getPokedexID() const { return pokedexID; }

	const char* getName() const { return name; }
	Element getElement() const { return element; }
	int getMaxHealth() const { return maxHealth; }

	std::vector<std::vector<sf::IntRect>> getAnimations() const { return animations; }

	int getNumAttacks() const { return numAttacks; }
	const Attack** getAttacks() const { return attacks; }

	std::string getSpriteFightFilename() const;
	std::string getSpriteOpponentFilename() const;



private:

	int pokedexID;

	const char* name;
	Element element;
	int maxHealth;

	std::vector<std::vector<sf::IntRect>> animations;

	int numAttacks;
	const Attack** attacks;
};
