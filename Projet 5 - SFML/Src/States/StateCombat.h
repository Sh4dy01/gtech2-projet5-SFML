#pragma once

#include "Manager/State/State.h"

#include <SFML/Graphics.hpp>


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
	virtual void render(sf::RenderWindow& window) override;
	virtual void keypress(int code) override;


private:

	void setTextDefaults(sf::Text& t);
	void setWidgetPosition(sf::Transformable& t, int x, int y);


private:

	Pokemon playerPokemon;
	Pokemon enemyPokemon;

	bool turn;

	CombatView view;

		/// Resources.
	sf::Texture* texBattleBackground;
	sf::Texture* texActionBackground;
	sf::Texture* texFightBackground;

		/// Sprites.
	sf::Sprite background;

	sf::Sprite playerSprite;
	sf::Sprite enemySprite;

	sf::Text playerName;
	sf::Text enemyName;
};
