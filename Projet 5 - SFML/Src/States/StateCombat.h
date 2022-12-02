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
		SELECT_ATTACK,
		ACTION_USE,
		ACTION_PET,
		EFFECTIVE,
		ENEMY_ATTACK,
		ENEMY_EFFECTIVE,
		END_COMBAT
	};


public:

	StateCombat();

		/// Sets default values to start a fight against a wild Pokemon.
		/// MUST be called BEFORE the state is entered.
	void initiateCombat(int enemyPokedex);

	void switchView(CombatView v);

	virtual void enter() override;
	virtual void leave() override;

	virtual void update(double deltaTime) override;
	virtual void render(sf::RenderWindow& window) override;
	virtual void keypress(int code) override;


private:

	void setTextDefaults(sf::Text& t);
	void setWidgetPosition(sf::Transformable& t, int x, int y);

	void updateArrowPosition();

	void triggerAttack(bool player);
	void resizeHealthBars();

	const std::vector<sf::Drawable*>& getCurrentSpriteSet() const;


private:

	Pokemon playerPokemon;
	Pokemon enemyPokemon;

	bool turn;
	bool enemyCalmedDown; // Petting.

		/// Selected action / attack.
	int action;
	int attack;

	int enemyAttack;

	CombatView view;

		/// Resources.
	sf::Texture* texBattleBackground;
	sf::Texture* texDialogBackground;
	sf::Texture* texActionBackground;
	sf::Texture* texActionPlayerBackground;
	sf::Texture* texFightBackground;

	sf::Texture* texPlayerPokemonSprite;
	sf::Texture* texEnemyPokemonSprite;

		/// Sprites.
	sf::Sprite background;

	sf::Sprite playerSprite;
	sf::Sprite enemySprite;

	sf::RectangleShape playerHP;
	sf::RectangleShape enemyHP;
	sf::Sprite arrowSprite;

	sf::Text playerName;
	sf::Text enemyName;

	sf::Text attacks[4];
	sf::Text attackType;

	sf::Text dialog;

	std::vector<sf::Drawable*> sprites;
	std::vector<sf::Drawable*> dialogSprites;
	std::vector<sf::Drawable*> actionSprites;
	std::vector<sf::Drawable*> attacksSprites;
};
