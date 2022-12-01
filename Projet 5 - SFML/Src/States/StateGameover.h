#pragma once

#include "Manager/State/State.h"



class StateGameover : public State
{
public:

	StateGameover();

	virtual void update(double d) override;
	virtual void render(sf::RenderWindow& window) override;

	virtual void keypress(int sfmlKeycode) override;
};
