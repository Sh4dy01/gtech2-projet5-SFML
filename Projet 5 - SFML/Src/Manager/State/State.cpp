#include "State.h"


State* State::currentState = 0;
State* State::nextState    = 0;


State::State()
{

}

void State::switchState(State* s)
{
	nextState = s;
}



void State::updateNextState()
{
	if (nextState) {

		currentState->leave();
		currentState = nextState;
		currentState->enter();

		nextState = 0;
	}
}

void State::updateNextState(sf::Vector2i vect)
{
	if (nextState) {

		currentState->leave();
		currentState = nextState;
		currentState->enter(vect);

		nextState = 0;
	}
}

void State::setDefaultState(State* s)
{
	if (currentState) {
		currentState->leave();
	}

	currentState = s;
	currentState->enter();
}

void State::setDefaultState(State* s, sf::Vector2i vect)
{
	if (currentState) {
		currentState->leave();
	}

	currentState = s;
	currentState->enter(vect);
}
