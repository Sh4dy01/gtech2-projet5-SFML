#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include "Manager/Game.h"

#include "Manager/State/State.h"


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
	while (Game::getWindow()->isOpen())
	{
		sf::Event event;
		while (Game::getWindow()->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Game::getWindow()->close();
		}

		// TODO : implement delta time.
		State::getCurrentState()->update(1.0 / 60.0);

		Game::getWindow()->clear();
		State::getCurrentState()->render();
		Game::getWindow()->display();

		State::updateNextState();
	}

	return EXIT_SUCCESS;
}
