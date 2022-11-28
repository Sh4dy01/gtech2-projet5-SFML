#include "Manager/Game.h"
#include "StateLevel.h"


StateLevel::StateLevel()
{

}

void StateLevel::enter()
{
	Game::getInstance().getMusicManager().PauseCurrentMusic();
	std::cout << "Music stopped" << std::endl;
}

void StateLevel::update(double deltaTime)
{

}

void StateLevel::render()
{
	Game::getInstance().test.render();
}
