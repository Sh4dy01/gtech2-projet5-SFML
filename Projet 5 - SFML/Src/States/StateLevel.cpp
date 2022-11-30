#include "Manager/Game.h"
#include "StateLevel.h"
#include <iostream>

StateLevel::StateLevel()
{

}

void StateLevel::enter()
{
	Map map = Game::getInstance().getCurrentMap();

	Game::getInstance().getMusicManager().PauseCurrentMusic();
	player.Initialize(0.8, sf::Vector2i(10, 10));

	for (int i = 0; i < map.getNbrEntity(); i++)
	{
		if (map.getType()[i] == "pokemon")
		{
			PokemonWorld* pokemon = new PokemonWorld(std::stoi(map.getEntityName()[i].c_str()));
			pokemon->SetCurrentDirection(map.getDir()[i]);
			pokemon->Initialize(1, sf::Vector2i(map.getPosX()[i], map.getPosY()[i]));
			elements.push_back(pokemon);
		}
	}
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
