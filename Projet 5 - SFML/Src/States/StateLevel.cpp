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
	currentMap = Game::getInstance().getMap();
	currentMap.LoadTiles();

	Game::getInstance().getMusicManager().PauseCurrentMusic();
	player.Initialize(0.8, sf::Vector2i(playerPosition.x, playerPosition.y));
	/*player.SpawnFollower(52);
	elements.push_back((sf::Drawable*)player.GetFollower());*/

	for (int i = 0; i < currentMap.getNbrEntity(); i++)
	{
		if (currentMap.getType()[i] == "pokemon")
		{
			PokemonWorld* pokemon = new PokemonWorld(std::stoi(currentMap.getEntityName()[i].c_str()));
			pokemon->SetCurrentDirection(currentMap.getDir()[i]);
			pokemon->Initialize(0.75, sf::Vector2i(currentMap.getPosX()[i], currentMap.getPosY()[i]));
			pokemon->FindAndSetDetectionRange();
			pokemons.push_back(pokemon);
			elements.push_back((sf::Drawable*)pokemon);
		}
	}
	elements.push_back(&player);
	camera = sf::View(player.getPosition(), sf::Vector2f(150, 150));
	Game::getInstance().setCamera(camera);
}

void StateLevel::leave()
{
	pokemons.clear();
	levelTiles.clear();
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
	for (Tile t : currentMap.getTiles())
	{
		window.draw(t);
	}

	for (sf::Drawable* e : elements) {
		window.draw(*e);
	}
}
