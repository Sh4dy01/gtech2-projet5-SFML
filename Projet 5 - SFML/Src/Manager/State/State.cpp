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

void State::setDefaultState(State* s)
{
	if (currentState) {
		currentState->leave();
	}

	currentState = s;
	currentState->enter();
}
