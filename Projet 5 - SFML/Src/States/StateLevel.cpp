#include "Manager/Game.h"
#include "Manager/Registry/Pokemon/PokemonWorld.h"
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
			std::cout << "creating " << map.getEntityName()[i] << " pokemon" << std::endl;
			PokemonWorld* pokemon = new PokemonWorld(std::stoi(map.getEntityName()[i].c_str()));
			pokemon->SetCurrentDirection(map.getDir()[i]);
			pokemon->Initialize(1, sf::Vector2i(map.getPosX()[i], map.getPosY()[i]));
			pokemons.push_back(pokemon);
			elements.push_back((sf::Drawable*)pokemon);
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

	for (PokemonWorld* p : pokemons) {
		if (p->IsPlayerDetected(&player))
		{
			//State::getCurrentState()->switchState(Game::getInstance().stateCombat);
			std::cout << "COMBAT STATE" << std::endl;
		}
	}
}

void StateLevel::render(sf::RenderWindow& window)
{
	Game::getInstance().getCurrentMap().render();

	for (sf::Drawable* e : elements) {
		window.draw(*e);
	}
}
