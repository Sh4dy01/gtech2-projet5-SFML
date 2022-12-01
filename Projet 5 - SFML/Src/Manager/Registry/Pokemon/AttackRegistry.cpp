#include "AttackRegistry.h"

#include "PokedexEntry.h"
#include "Attack.h"



const Attack& AttackRegistry::PUNCH         = attacks[0];
const Attack& AttackRegistry::TACKLE        = attacks[1];
const Attack& AttackRegistry::SCRATCH       = attacks[2];
const Attack& AttackRegistry::QUICK_ATTACK  = attacks[3];
const Attack& AttackRegistry::SPLASH        = attacks[4];
const Attack& AttackRegistry::VINE_WHIP     = attacks[5];
const Attack& AttackRegistry::EMBER         = attacks[6];
const Attack& AttackRegistry::WATER_GUN     = attacks[7];
const Attack& AttackRegistry::THUNDER_SHOCK = attacks[8];
const Attack& AttackRegistry::ROLLOUT       = attacks[9];
const Attack& AttackRegistry::CONFUSION     = attacks[10];
const Attack& AttackRegistry::JUDGMENT      = attacks[11];
const Attack& AttackRegistry::HYPER_BEAM    = attacks[12];
const Attack& AttackRegistry::GROWL			= attacks[13];



const Attack AttackRegistry::attacks[] =
{
	Attack("Punch",         10, Element::NORMAL),
	Attack("Tackle",        40, Element::NORMAL),
	Attack("Scratch",       40, Element::NORMAL),
	Attack("Quick attack",  40, Element::NORMAL),
	Attack("Splash",         0, Element::NORMAL),

	Attack("Vine whip",     40, Element::GRASS),
	Attack("Ember",         40, Element::FIRE),
	Attack("Water gun",     40, Element::WATER),
	Attack("Thunder shock", 40, Element::ELECTRIC),
	Attack("Rollout",       30, Element::GROUND),
	Attack("Confusion",     50, Element::PSYCHIC),
	
	Attack("Judgment",     100, Element::NORMAL),
	Attack("Hyper beam",   120, Element::NORMAL),
	Attack("Growl",			 0, Element::NORMAL),
};
