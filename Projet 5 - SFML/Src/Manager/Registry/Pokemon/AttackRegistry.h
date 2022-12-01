#pragma once

#include <vector>

class Attack;



class AttackRegistry
{
public:

	static const Attack& PUNCH;
	static const Attack& TACKLE;
	static const Attack& SCRATCH;
	static const Attack& GROWL;
	static const Attack& QUICK_ATTACK;
	static const Attack& SPLASH;
	static const Attack& VINE_WHIP;
	static const Attack& EMBER;
	static const Attack& WATER_GUN;
	static const Attack& THUNDER_SHOCK;
	static const Attack& ROLLOUT;
	static const Attack& CONFUSION;
	static const Attack& JUDGMENT;
	static const Attack& HYPER_BEAM;

private:

	static const Attack attacks[];
};
