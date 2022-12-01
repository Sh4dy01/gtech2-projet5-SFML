#include "Manager/Game.h"
#include "StateCombat.h"

#include "Manager/Resource/ResourceManager.h"
#include "Manager/Resource/MusicManager.h"
#include "Manager/Resource/SoundManager.h"
#include "Manager/Registry/Pokemon/PokemonRegistry.h"

#include <SFML/Graphics.hpp>



StateCombat::StateCombat()
	: turn(true)
{
	
}

void StateCombat::initiateCombat(int enemyPokedex)
{
	enemyPokemon.pokedexID = enemyPokedex;
}

void StateCombat::switchView(CombatView v)
{
	view = v;

	switch (v)
	{
	case StateCombat::INTRO:
		{
			std::string s = "A wild ";
			s += PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID)->getName();
			s += "\nappears!";
			dialog.setString(s);
		}
		break;

	case StateCombat::SELECT_ACTION:
		// Change visibility.
		background.setTexture(playerPokemon.pokedexID == 0 ? *texActionPlayerBackground : *texActionBackground);

		action = 0;
		this->updateArrowPosition();

		dialog.setString("");
		break;

	case StateCombat::SELECT_ATTACK:
		// Change visibility.
		background.setTexture(*texFightBackground);

		attack = 0;
		this->updateArrowPosition();

		break;

	case StateCombat::ACTION_USE:
		{
			background.setTexture(*texDialogBackground);

			const PokedexEntry* p = PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID);
			const PokedexEntry* e = PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID);

			std::string actionText;

			switch (action) {
			case 0:
				actionText += p->getName();
				actionText += " used\n";
				actionText += p->getAttacks()[attack]->getName();
				actionText += '!';
				break;
			case 3:
				actionText += p->getName();
				actionText += " tries to flee, but\n";
				actionText += e->getName();
				actionText += " is too fast!";
				break;
			}
			
			dialog.setString(actionText);
		}
		break;

	case StateCombat::ENEMY_ATTACK:
		{
			background.setTexture(*texDialogBackground);

			const PokedexEntry* e = PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID);

			enemyAttack = rand() % e->getNumAttacks();

			std::string s;
			s += e->getName();
			s += " used\n";
			s += e->getAttacks()[enemyAttack]->getName();
			s += '!';
			dialog.setString(s);
		}
		break;

	case StateCombat::EFFECTIVE:
		{
			if (action == 3)
				dialog.setString("It has no effect.");
			else
				dialog.setString("It is not very effective...");
		}
		break;
	case StateCombat::ENEMY_EFFECTIVE:
		{
			dialog.setString("");
		}
		break;
	}
}



void StateCombat::enter(sf::Vector2i)
{
	Game::getInstance().getMusicManager().LoadMusicAndPlay("battle-music");
	Game::getInstance().getSoundManager().LoadSound("select-sound");

	// Default values.
	playerPokemon.pokedexID = 0;
	const PokedexEntry* playerPokemonType = PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID);
	const PokedexEntry* enemyPokemonType  = PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID);

	playerPokemon.health = playerPokemonType->getMaxHealth();
	enemyPokemon.health  = enemyPokemonType->getMaxHealth();
	playerPokemon.level  = 1;
	enemyPokemon.level   = 1;

	this->switchView(INTRO);


	// Textures.
	texBattleBackground       = &Game::getInstance().getResourceManager().loadImage("battle_background.png");
	texDialogBackground       = &Game::getInstance().getResourceManager().loadImage("battle_dialog_background.png");
	texActionBackground       = &Game::getInstance().getResourceManager().loadImage("battle_action_background.png");
	texActionPlayerBackground = &Game::getInstance().getResourceManager().loadImage("battle_action_player_background.png");
	texFightBackground        = &Game::getInstance().getResourceManager().loadImage("battle_fight_background.png");

	texPlayerPokemonSprite = &Game::getInstance().getResourceManager().loadImage(playerPokemonType->getSpriteFightFilename().c_str());
	texEnemyPokemonSprite  = &Game::getInstance().getResourceManager().loadImage(enemyPokemonType->getSpriteOpponentFilename().c_str());
	sf::Texture& arrow  = Game::getInstance().getResourceManager().loadImage("arrow.png");


	background.setTexture(*texBattleBackground);
	background.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);
	sprites.push_back(&background);

	this->setWidgetPosition(playerSprite, 2, 7);
	playerSprite.setTexture(*texPlayerPokemonSprite);
	playerSprite.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);
	sprites.push_back(&playerSprite);

	this->setWidgetPosition(enemySprite, 12, 1);
	enemySprite.setTexture(*texEnemyPokemonSprite);
	enemySprite.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);
	sprites.push_back(&enemySprite);

	playerHP.setFillColor(sf::Color(0, 184, 0));
	playerHP.setPosition(96.0F / 160.0F * GAME_SIZE_X, 83.0F / 160.0F * GAME_SIZE_Y);
	playerHP.setSize(sf::Vector2f(48 / 160.0F * GAME_SIZE_X, 2 / 160.0F * GAME_SIZE_Y));
	sprites.push_back(&playerHP);

	enemyHP.setFillColor(sf::Color(0, 184, 0));
	enemyHP.setPosition(32.0F / 160.0F * GAME_SIZE_X, 27.0F / 160.0F * GAME_SIZE_Y);
	enemyHP.setSize(sf::Vector2f(48 / 160.0F * GAME_SIZE_X, 2 / 160.0F * GAME_SIZE_Y));
	sprites.push_back(&enemyHP);

	arrowSprite.setTexture(arrow);
	arrowSprite.setScale(GAME_SIZE_X / 160.0F, GAME_SIZE_Y / 160.0F);
	actionSprites.push_back(&arrowSprite);
	attacksSprites.push_back(&arrowSprite);

	
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
	attackType.setFillColor(sf::Color(0, 0, 0));
	attacksSprites.push_back(&attackType);

	for (int i = 0; i < 4; ++i) {
		this->setTextDefaults(attacks[i]);
		this->setWidgetPosition(attacks[i], 6, 14 + i);
		attacks[i].setFillColor(sf::Color(0, 0, 0, 255));

		if (i < playerPokemonType->getNumAttacks()) {
			attacks[i].setString(playerPokemonType->getAttacks()[i]->getName());
		}
		else {
			attacks[i].setString("---");
		}

		attacksSprites.push_back(&attacks[i]);
	}

	this->setTextDefaults(dialog);
	this->setWidgetPosition(dialog, 1, 14);
	dialog.setFillColor(sf::Color(0, 0, 0, 255));
	dialogSprites.push_back(&dialog);
}

void StateCombat::leave()
{

}

void StateCombat::update(double deltaTime)
{
	
}

void StateCombat::render(sf::RenderWindow& window)
{
	for (const sf::Drawable* d : sprites) {
		Game::getInstance().getWindow().draw(*d);
	}

	const std::vector<sf::Drawable*>& s = this->getCurrentSpriteSet();
	for (const sf::Drawable* d : s) {
		Game::getInstance().getWindow().draw(*d);
	}
}

void StateCombat::keypress(int code)
{
	switch (code) {
	case sf::Keyboard::Space:
		
		switch (view) {
		case INTRO:         this->switchView(SELECT_ACTION); break;
		case SELECT_ACTION:
			{
				if (action == 0) this->switchView(SELECT_ATTACK);
				//else if (action == 2)
				else if (action == 3) this->switchView(ACTION_USE);
			}
			break;
		case SELECT_ATTACK:
			if (attack < PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID)->getNumAttacks()) {
				this->switchView(ACTION_USE);
			}
			break;
		case ACTION_USE:
			this->triggerAttack(true);
			this->switchView(EFFECTIVE);
			break;
		case ENEMY_ATTACK:
			this->triggerAttack(false);
			this->switchView(ENEMY_EFFECTIVE);
			break;
		case EFFECTIVE:
			this->switchView(ENEMY_ATTACK);
			break;
		case ENEMY_EFFECTIVE:
			this->switchView(SELECT_ACTION);
			break;
		}
		break;

	case sf::Keyboard::Escape:

		this->switchView(SELECT_ACTION);
		break;


		// Navigation.
	case sf::Keyboard::Z:
		if (action / 2 == 1) action -= 2;
		if (attack > 0) attack--;
		this->updateArrowPosition();
		break;
	case sf::Keyboard::S:
		if (action / 2 == 0) action += 2;
		if (attack < 3) attack++;
		this->updateArrowPosition();
		break;
	case sf::Keyboard::D:
		if (action % 2 == 0) action++;
		this->updateArrowPosition();
		break;
	case sf::Keyboard::Q:
		if (action % 2 == 1) action--;
		this->updateArrowPosition();
		break;
	}
}



void StateCombat::setTextDefaults(sf::Text& t)
{
	const float textScaling = 0.89F;

	sf::Font& font = Game::getInstance().getResourceManager().loadFont("Pokemon-Classic.ttf");
	((sf::Texture&) font.getTexture(8)).setSmooth(false);
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
	Game::getInstance().getSoundManager().PlaySound("select-sound");

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

void StateCombat::triggerAttack(bool isPlayer)
{
	const PokedexEntry* player = PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID);
	const PokedexEntry* enemy  = PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID);

	const Attack* a = 0;

	const float DAMAGE_MULTIPLIER = 0.4F;

	if (isPlayer) {
		if (attack < player->getNumAttacks()) {
			a = player->getAttacks()[attack];
			enemyPokemon.health -= a->getDamage() * DAMAGE_MULTIPLIER;
		}
	}
	else {
		a = enemy->getAttacks()[enemyAttack];
		playerPokemon.health -= a->getDamage() * DAMAGE_MULTIPLIER;
	}

	this->resizeHealthBars();
}

void StateCombat::resizeHealthBars()
{
	const PokedexEntry* playerPokemonType = PokemonRegistry::getPokemonByPokedexNumber(playerPokemon.pokedexID);
	const PokedexEntry* enemyPokemonType = PokemonRegistry::getPokemonByPokedexNumber(enemyPokemon.pokedexID);

	int hbsize = 48 * playerPokemon.health / playerPokemonType->getMaxHealth();
	playerHP.setSize(sf::Vector2f(hbsize / 160.0F * GAME_SIZE_X, playerHP.getSize().y));

	hbsize = 48 * enemyPokemon.health / enemyPokemonType->getMaxHealth();
	enemyHP.setSize(sf::Vector2f(hbsize / 160.0F * GAME_SIZE_X, enemyHP.getSize().y));
}

const std::vector<sf::Drawable*>& StateCombat::getCurrentSpriteSet() const
{
	switch (view) {
	case INTRO:
	case ACTION_USE:
	case ENEMY_ATTACK:
	case EFFECTIVE:
	case ENEMY_EFFECTIVE:
	default:
		return dialogSprites;
	case SELECT_ACTION:
		return actionSprites;
	case SELECT_ATTACK:
		return attacksSprites;
	}
}
