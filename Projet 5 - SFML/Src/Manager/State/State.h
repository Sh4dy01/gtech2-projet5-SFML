#pragma once


class State
{
public:

	State();

		/// Called when the state manager switches to this state.
	virtual void enter() { }

		/// Called when the state manager exits this state.
	virtual void leave() { }

	virtual void update( double deltaTime ) = 0;
	virtual void render() = 0;
	virtual void keypress( int sfmlKeycode ) { }

	static void switchState( State* s );

		/// Proceed with a state switch, if necessary.
	static void updateNextState();

	static State* getCurrentState() { return currentState; }

	static void setDefaultState(State* s);



private:

	static State* currentState;
	static State* nextState;
};
