#include "Manager/Game.h"
#include "StateCombat.h"

#include "Manager/Resource/ResourceManager.h"
#include "Manager/Audio/MusicManager.h"
#include "Manager/Registry/Pokemon/PokemonRegistry.h"

#include <SFML/Graphics.hpp>



StateCombat::StateCombat()
	: turn(true)
{
	
}

void StateCombat::switchView(CombatView v)
{
	view = v;

	switch (v)
	{
	case StateCombat::INTRO:
		break;

	case StateCombat::SELECT_ACTION:
		// Change visibility.
		background.setTexture(*texActionBackground);
		playerSprite.setColor(sf::Color(255, 255, 255, 255));
		arrowSprite.setColor(sf::Color(255, 255, 255, 255));
		attackType.setFillColor(sf::Color(0, 0, 0, 0));
		for (int i = 0; i < 4; ++i) attacks[i].setFillColor(sf::Color(0, 0, 0, 0));

		action = 0;
		this->updateArrowPosition();

		break;

	case StateCombat::SELECT_ATTACK:
		// Change visibility.
		background.setTexture(*texFightBackground);
		playerSprite.setColor(sf::Color(0, 0, 0, 0));
		arrowSprite.setColor(sf::Color(255, 255, 255, 255));
		attackType.setFillColor(sf::Color(0, 0, 0, 255));
		for (int i = 0; i < 4; ++i) attacks[i].setFillColor(sf::Color(0, 0, 0, 255));

		attack = 0;
		this->updateArrowPosition();

		break;
	}
}



void StateCombat::enter()
{
	view = INTRO;

	Game::getInstance().getMusicManager().LoadMusicAndPlay("battle-music");

	playerPokemon.pokedexID = 0;
	enemyPokemon.pokedexID = 63;
	const PokedexEntry* playerPokemonType = PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID);
	const PokedexEntry* enemyPokemonType  = PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID);


	// Textures.
	texBattleBackground = &Game::getInstance().getResourceManager().loadImage("battle_background.png");
	texActionBackground = &Game::getInstance().getResourceManager().loadImage("battle_action_background.png");
	texFightBackground  = &Game::getInstance().getResourceManager().loadImage("battle_fight_background.png");

	texPlayerPokemonSprite = &Game::getInstance().getResourceManager().loadImage(playerPokemonType->getSpriteFightFilename().c_str());
	texEnemyPokemonSprite  = &Game::getInstance().getResourceManager().loadImage(enemyPokemonType->getSpriteOpponentFilename().c_str());
	sf::Texture& arrow  = Game::getInstance().getResourceManager().loadImage("arrow.png");


	background.setTexture(*texBattleBackground);
	background.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);
	sprites.push_back(&background);

	arrowSprite.setTexture(arrow);
	arrowSprite.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);
	arrowSprite.setColor(sf::Color(255, 255, 255, 0));
	sprites.push_back(&arrowSprite);

	this->setWidgetPosition(playerSprite, 2, 7);
	playerSprite.setTexture(*texPlayerPokemonSprite);
	playerSprite.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);
	sprites.push_back(&playerSprite);

	this->setWidgetPosition(enemySprite, 12, 1);
	enemySprite.setTexture(*texEnemyPokemonSprite);
	enemySprite.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);
	sprites.push_back(&enemySprite);

	
	// Texts.
	this->setTextDefaults(playerName);
	this->setWidgetPosition(playerName, 10, 8);
	playerName.setString(playerPokemonType->getName());
	playerName.setFillColor(sf::Color(0, 0, 0, 255));
	sprites.push_back(&playerName);

	this->setTextDefaults(enemyName);
	this->setWidgetPosition(enemyName, 1, 1);
	enemyName.setString(enemyPokemonType->getName());
	enemyName.setFillColor(sf::Color(0, 0, 0, 255));
	sprites.push_back(&enemyName);

	this->setTextDefaults(attackType);
	this->setWidgetPosition(attackType, 2, 11);
	sprites.push_back(&attackType);

	for (int i = 0; i < 4; ++i) {
		this->setTextDefaults(attacks[i]);
		this->setWidgetPosition(attacks[i], 6, 14 + i);
		attacks[i].setFillColor(sf::Color(0, 0, 0, 0));

		if (i < playerPokemonType->getNumAttacks()) {
			attacks[i].setString(playerPokemonType->getAttacks()[i]->getName());
		}
		else {
			attacks[i].setString("---");
		}

		sprites.push_back(&attacks[i]);
	}
}

void StateCombat::leave()
{

}

void StateCombat::update(double deltaTime)
{
	
}

void StateCombat::render()
{
	for (const sf::Drawable* d : sprites) {
		Game::getInstance().getWindow().draw(*d);
	}
}

void StateCombat::keypress(int code)
{
	switch (code) {
	case sf::Keyboard::Space:
		
		switch (view) {
		case INTRO:         this->switchView(SELECT_ACTION); break;
		case SELECT_ACTION: this->switchView(SELECT_ATTACK); break;
		case SELECT_ATTACK:
			{
				this->triggerAttack();
				this->switchView(SELECT_ACTION);
			}
			break;
		}
		break;

	case sf::Keyboard::Escape:

		this->switchView(SELECT_ACTION);
		break;


		// Navigation.
	case sf::Keyboard::Up:
		if (action / 2 == 1) action -= 2;
		if (attack > 0) attack--;
		this->updateArrowPosition();
		break;
	case sf::Keyboard::Down:
		if (action / 2 == 0) action += 2;
		if (attack < 3) attack++;
		this->updateArrowPosition();
		break;
	case sf::Keyboard::Right:
		if (action % 2 == 0) action++;
		this->updateArrowPosition();
		break;
	case sf::Keyboard::Left:
		if (action % 2 == 1) action--;
		this->updateArrowPosition();
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
	t.setPosition(GAME_SIZE_X / 20.0F * x, GAME_SIZE_Y / 20.0F * y);
}

void StateCombat::updateArrowPosition()
{
	switch (view) {
	case SELECT_ACTION:
		this->setWidgetPosition(arrowSprite, (action % 2) * 6 + 9, (action / 2) * 2 + 15);
		break;

	case SELECT_ATTACK:
		{
			this->setWidgetPosition(arrowSprite, 5, attack + 14);

			const PokedexEntry* p = PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID);
			if (attack < p->getNumAttacks())
				attackType.setString(PokemonRegistry::getElementName(p->getAttacks()[attack]->getElement()));
			else
				attackType.setString("");
		}
		break;
	}
}

void StateCombat::triggerAttack()
{
	const PokedexEntry* player = PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID);
	const PokedexEntry* enemy  = PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID);

	const Attack* a;

	if (turn) {
		a = player->getAttacks()[attack];
		enemyPokemon.health -= a->getDamage();
	}
	else {
		a = enemy->getAttacks()[rand() % enemy->getNumAttacks()];
		playerPokemon.health -= a->getDamage();
	}
}
