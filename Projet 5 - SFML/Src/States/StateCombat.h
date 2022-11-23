#pragma once

#include "Manager/State/State.h"


class StateCombat : public State
{
public:

	StateCombat();

	virtual void update(double deltaTime) override;
	virtual void render() override;
};
