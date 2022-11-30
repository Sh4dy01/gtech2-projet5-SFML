#pragma once

#include "Manager/State/State.h"

#include <SFML/Graphics.hpp>

class Attack;


class StateCombat : public State
{
public:

	class Pokemon
	{
	public:

		// Type of pokemon.
		int pokedexID;

		// Current health.
		int health;

		// Pokemon's level.
		int level;
	};

	enum CombatView
	{
		INTRO,
		SELECT_ACTION,
		SELECT_ATTACK
	};


public:

	StateCombat();

	void switchView(CombatView v);

	virtual void enter() override;
	virtual void leave() override;

	virtual void update(double deltaTime) override;
	virtual void render() override;
	virtual void keypress(int code) override;


private:

	void setTextDefaults(sf::Text& t);
	void setWidgetPosition(sf::Transformable& t, int x, int y);

	void updateArrowPosition();

	void triggerAttack();


private:

	Pokemon playerPokemon;
	Pokemon enemyPokemon;

	bool turn;

		/// Selected action / attack.
	int action;
	int attack;

	CombatView view;

		/// Resources.
	sf::Texture* texBattleBackground;
	sf::Texture* texActionBackground;
	sf::Texture* texFightBackground;

	sf::Texture* texPlayerPokemonSprite;
	sf::Texture* texEnemyPokemonSprite;

		/// Sprites.
	sf::Sprite background;

	sf::Sprite playerSprite;
	sf::Sprite enemySprite;
	sf::Sprite arrowSprite;

	sf::Text playerName;
	sf::Text enemyName;

	sf::Text attacks[4];
	sf::Text attackType;

	std::vector<sf::Drawable*> sprites;
};
