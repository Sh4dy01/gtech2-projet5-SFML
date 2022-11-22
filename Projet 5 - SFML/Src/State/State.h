#pragma once


class State
{
public:

	State();

		/// Called when the state manager switches to this state.
	virtual void enter() = 0;

		/// Called when the state manager exits this state.
	virtual void leave() = 0;

	virtual void update( double deltaTime ) = 0;
	virtual void render() = 0;

	static void switchState( State* s );

		/// Proceed with a state switch, if necessary.
	static void updateNextState();

	static State* getCurrentState() { return currentState; }



private:

	static State* currentState;
	static State* nextState;
};
