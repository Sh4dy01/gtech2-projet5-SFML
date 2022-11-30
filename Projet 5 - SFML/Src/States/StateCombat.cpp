#include "Manager/Game.h"
#include "StateCombat.h"

#include "Manager/Resource/ResourceManager.h"
#include "Manager/Registry/Pokemon/PokemonRegistry.h"

#include <SFML/Graphics.hpp>


StateCombat::StateCombat()
	: turn(true)
{
	
}

void StateCombat::switchView(CombatView v)
{
	switch (v)
	{
	case StateCombat::INTRO:
		break;
	case StateCombat::SELECT_ACTION:
		background.setTexture(*texActionBackground);
		break;
	case StateCombat::SELECT_ATTACK:
		background.setTexture(*texFightBackground);
		break;
	}

	view = v;
}


void StateCombat::enter()
{
	view = INTRO;

	texBattleBackground = &Game::getInstance().getResourceManager().loadImage("battle_background.png");
	texActionBackground = &Game::getInstance().getResourceManager().loadImage("battle_action_background.png");
	texFightBackground  = &Game::getInstance().getResourceManager().loadImage("battle_fight_background.png");

	background.setTexture(*texBattleBackground);
	background.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);

	playerPokemon.pokedexID = 0;
	enemyPokemon.pokedexID = 1;

	
	// Texts.
	this->setTextDefaults(playerName);
	this->setWidgetPosition(playerName, 10, 8);
	playerName.setString(PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID)->getName());
	playerName.setFillColor(sf::Color(0, 0, 0, 255));

	this->setTextDefaults(enemyName);
	this->setWidgetPosition(enemyName, 1, 1);
	enemyName.setString(PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID)->getName());
	enemyName.setFillColor(sf::Color(0, 0, 0, 255));
}

void StateCombat::leave()
{

}

void StateCombat::update(double deltaTime)
{

}

void StateCombat::render(sf::RenderWindow& window)
{
	Game::getInstance().getWindow().draw(background);

	Game::getInstance().getWindow().draw(playerSprite);
	Game::getInstance().getWindow().draw(enemySprite);

	// TODO : Draw pokemon names and stats.
	Game::getInstance().getWindow().draw(playerName);
	Game::getInstance().getWindow().draw(enemyName);
}

void StateCombat::keypress(int code)
{
	switch (code) {
	case sf::Keyboard::Space:
		
		switch (view) {
		case INTRO:         this->switchView(SELECT_ACTION); break;
		case SELECT_ACTION: this->switchView(SELECT_ATTACK); break;
		case SELECT_ATTACK: this->switchView(SELECT_ACTION); break;
		}
		break;

	case sf::Keyboard::Escape:

		this->switchView(SELECT_ACTION);
		break;
	}
}



void StateCombat::setTextDefaults(sf::Text& t)
{
	const float textScaling = 0.89F;

	sf::Font& font = Game::getInstance().getResourceManager().loadFont("Pokemon-Classic.ttf");
	t.setFont(font);
	t.setCharacterSize(8);
	t.setScale(GAME_SIZE_X / 160.0F * textScaling, GAME_SIZE_Y / 160.0F * textScaling);
}

void StateCombat::setWidgetPosition(sf::Transformable& t, int x, int y)
{
	t.setPosition(GAME_SIZE_X / 20.0F * x + 1.6F, GAME_SIZE_Y / 20.0F * y);
}
