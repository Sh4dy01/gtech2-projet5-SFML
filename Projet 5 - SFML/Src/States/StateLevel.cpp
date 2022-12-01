#include "Manager/Game.h"
#include "Manager/Registry/Pokemon/PokemonWorld.h"
#include "StateLevel.h"
#include "Manager/Follower.h"
#include "Manager/SpriteConfig.h"
#include <iostream>

StateLevel::StateLevel() : IsIntro(false), meteor("meteor", false)
{
}

StateLevel::StateLevel(sf::Vector2i vect) : IsIntro(false), meteor("meteor", false)
{
	this->playerPos = vect;
	IsIntroPlayed = false;
}

void StateLevel::StartIntro() {
	IsIntro = true;
	player.SetMovementAbility(false);
	meteor.Initialize(sf::IntRect(0,0,1024,1024), 0.5, sf::Vector2i(3, 0));
	meteor.setColor(sf::Color(255, 255, 255, 230));
}

void StateLevel::enter()
{
	if (Game::getInstance().getMusicManager().GetCurrentMusic()->getStatus() != Game::getInstance().getMusicManager().GetCurrentMusic()->Playing)
	{
		Game::getInstance().getMusicManager().LoadMusicAndPlay("chill");
	}

	currentMap = Game::getInstance().getMap();
	currentMap.LoadTiles();
	
	player.Initialize(0.8, sf::Vector2i(playerPos.x, playerPos.y));
	if (player.IsFollowerSpawned())
	{
		player.GetFollower()->SetToPlayerPosition();
	}

	for (int i = 0; i < currentMap.getNbrEntity(); i++)
	{
		if (currentMap.getType()[i] == "pokemon")
		{
			PokemonWorld* pokemon = new PokemonWorld(std::stoi(currentMap.getEntityName()[i].c_str()));
			pokemon->Initialize(0.75, sf::Vector2i(currentMap.getPosX()[i], currentMap.getPosY()[i]));
			pokemon->SetCurrentDirection(currentMap.getDir()[i]);
			pokemon->FindAndSetDetectionRange();
			pokemons.push_back(pokemon);
			elements.push_back((sf::Drawable*)pokemon);
		}
	}
	elements.push_back(&player);
	camera = sf::View(player.getPosition(), sf::Vector2f(160, 160));
	Game::getInstance().setCamera(camera);

	if (currentMap.getName() == "startMap" && !IsIntroPlayed)
		StartIntro();
}

void StateLevel::leave()
{
	pokemons.clear();
	elements.clear();
	levelTiles.clear();
}

void StateLevel::update(double deltaTime)
{
	if (IsIntro)
	{
		if (count <= 3)
		{
			meteor.move(1, 1);
			camera.move(1,0);
		}
		else {
			IsIntro = false;
			IsIntroPlayed = true;
			player.SetMovementAbility(true);
			elements.pop_back();
		}
		count += deltaTime;
	}

	if (player.CanMove()) {
		player.CheckInputs(deltaTime);
		camera.setCenter(player.getPosition());
		Game::getInstance().setCamera(camera);
	}

	for (PokemonWorld* p : pokemons) {
		if (p->IsPlayerDetected(&player))
		{
			//State::getCurrentState()->switchState(Game::getInstance().stateCombat);
			std::cout << "COMBAT STATE" << std::endl;
		}
	}
	
	sf::Vector2i event = Game::getInstance().getResourceManager().eventModifyCurrentMap(player.getPosition().x / SPRITE_SIZE, player.getPosition().y / SPRITE_SIZE);
	if (event.x != -1 || event.y != -1) {
		this->playerPos = event;
		this->switchState(this);
		this->updateNextState();
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

Player& StateLevel::getPlayer()
{
	return this->player;
}
