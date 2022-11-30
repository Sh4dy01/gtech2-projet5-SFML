#include "Manager/Game.h"
#include "Manager/Registry/Pokemon/PokemonWorld.h"
#include "StateLevel.h"
#include <iostream>

StateLevel::StateLevel()
{

}

void StateLevel::enter()
{
	currentMap = Game::getInstance().getCurrentMap();
	currentMap.LoadTiles();

	Game::getInstance().getMusicManager().PauseCurrentMusic();
	player.Initialize(0.8, sf::Vector2i(14, 14));

	for (int i = 0; i < currentMap.getNbrEntity(); i++)
	{
		if (currentMap.getType()[i] == "pokemon")
		{
			PokemonWorld* pokemon = new PokemonWorld(std::stoi(currentMap.getEntityName()[i].c_str()));
			pokemon->SetCurrentDirection(currentMap.getDir()[i]);
			pokemon->Initialize(1, sf::Vector2i(currentMap.getPosX()[i], currentMap.getPosY()[i]));
			pokemon->FindAndSetDetectionRange();
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
	for (Tile t : currentMap.getTiles())
	{
		window.draw(t);
	}

	for (sf::Drawable* e : elements) {
		window.draw(*e);
	}
}
