#pragma once

#include "Manager/State/State.h"


class StateLevel : public State
{
public:

	StateLevel();

	virtual void enter() override;
	virtual void update(double deltaTime) override;
	virtual void render() override;
};
