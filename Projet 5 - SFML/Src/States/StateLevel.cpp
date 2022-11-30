#include "Manager/Game.h"
#include "StateLevel.h"


StateLevel::StateLevel()
{

}

void StateLevel::enter()
{
	Game::getInstance().getMusicManager().PauseCurrentMusic();
	player.Initialize(1, sf::Vector2i(10, 10));
	elements.push_back(&player);

	camera = sf::View(player.getPosition(), sf::Vector2f(150, 150));
	Game::getInstance().setCamera(camera);
}

void StateLevel::update(double deltaTime)
{
	player.CheckAllDirections(deltaTime);
	camera.setCenter(player.getPosition());
	Game::getInstance().setCamera(camera);
}

void StateLevel::render(sf::RenderWindow& window)
{
	Game::getInstance().getCurrentMap().render();

	for (sf::Drawable* e : elements) {
		window.draw(*e);
	}
}
