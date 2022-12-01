#pragma once
#include <vector>
#include "SFML/Graphics/Drawable.hpp"
#include <SFML/Graphics/RenderWindow.hpp>

class State
{
public:

	State();

		/// Called when the state manager switches to this state.
	virtual void enter() { }
	virtual void enter(sf::Vector2i) { }

		/// Called when the state manager exits this state.
	virtual void leave() { }

	virtual void update( double deltaTime ) = 0;
	virtual void render(sf::RenderWindow& window) = 0;
	virtual void keypress( int sfmlKeycode ) { }

	static void switchState( State* s );

		/// Proceed with a state switch, if necessary.
	static void updateNextState();
	static void updateNextState(sf::Vector2i);

	void addElement(sf::Drawable* e) { elements.push_back(e); };

	static State* getCurrentState() { return currentState; }

	static void setDefaultState(State* s);
	static void setDefaultState(State* s, sf::Vector2i vect);



private:

	static State* currentState;
	static State* nextState;

protected:

	std::vector<sf::Drawable*> elements;
};
