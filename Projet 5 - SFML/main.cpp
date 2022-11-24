#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Manager/Game.h"

#include "Manager/State/State.h"

#include <chrono>


int main()
{
	Game::Initialization();

	sf::Clock clock;

	// Load a music to play
	/*sf::Music music;
	if (!music.openFromFile("nice_music.ogg"))
		return EXIT_FAILURE;*/
	//music.play();
	// 

	double deltaTime = 1.0 / 60.0;

	while (Game::getWindow()->isOpen())
	{
		auto start = std::chrono::high_resolution_clock::now();

		sf::Event event;
		while (Game::getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Game::getWindow()->close();

		}

		// TODO : implement delta time.
		State::getCurrentState()->update(deltaTime);

		Game::getWindow()->clear();
		State::getCurrentState()->render();
		Game::getWindow()->display();

		State::updateNextState();

		auto end = std::chrono::high_resolution_clock::now();
		deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() / 1000000.0;
	}

	return EXIT_SUCCESS;
}
