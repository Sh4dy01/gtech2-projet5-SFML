#pragma once

#include "State/State.h"


class StateLevel : public State
{
public:

	StateLevel();

	virtual void update(double deltaTime) override;
	virtual void render() override;
};
