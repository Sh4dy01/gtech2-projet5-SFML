#pragma once

#include "Manager/State/State.h"
#include "Manager/PlayerController.h"


class StateLevel : public State
{
public:

	StateLevel();

	virtual void enter() override;
	virtual void update(double deltaTime) override;
	virtual void render(sf::RenderWindow& window) override;

private:

	sf::View camera;
	Player player;

};
