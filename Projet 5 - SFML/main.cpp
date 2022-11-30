#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Manager/Game.h"

#include "Manager/State/State.h"

#include <chrono>


int main()
{
	srand(time(0));

	Game game;
	game.Initialization();

	sf::Clock clock;

	double deltaTime = 1.0 / 60.0;

	while (game.getWindow().isOpen())
	{
		auto start = std::chrono::high_resolution_clock::now();

		sf::Event event;
		while (game.getWindow().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				game.getWindow().close();
			else if (event.type == sf::Event::KeyPressed)
				State::getCurrentState()->keypress(event.key.code);
		}

		// TODO : implement delta time.
		State::getCurrentState()->update(deltaTime);

		game.getWindow().clear();
		State::getCurrentState()->render(game.getWindow());
		game.getWindow().display();

		State::updateNextState();

		auto end = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
	}

	return EXIT_SUCCESS;
}
