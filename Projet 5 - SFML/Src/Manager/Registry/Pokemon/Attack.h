#pragma once

#include "PokedexEntry.h"


class Attack
{
public:

	Attack(const char* name, int damage, Element e);

	const char* getName()    const { return name; }
	int         getDamage()  const { return damage; }
	Element     getElement() const { return element; }


private:

	const char* name;
	int damage;
	Element element;
};
