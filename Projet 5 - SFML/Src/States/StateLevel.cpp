#include "Manager/Game.h"
#include "Manager/Registry/Pokemon/PokemonWorld.h"
#include "StateLevel.h"
#include "Manager/SpriteConfig.h"
#include <iostream>

StateLevel::StateLevel()
{

}

void StateLevel::enter(sf::Vector2i playerPosition)
{
	Map map = Game::getInstance().getMap();

	Game::getInstance().getMusicManager().PauseCurrentMusic();
	player.Initialize(0.8, sf::Vector2i(playerPosition.x, playerPosition.y));

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
	
	sf::Vector2i event = Game::getInstance().getResourceManager().eventModifyCurrentMap(player.getPosition().x / SPRITE_SIZE, player.getPosition().y / SPRITE_SIZE);
	if (event.x != -1 || event.y != -1) {
		this->enter(event);
	}
}

void StateLevel::render(sf::RenderWindow& window)
{
	Game::getInstance().getMap().render();

	for (sf::Drawable* e : elements) {
		window.draw(*e);
	}
}
