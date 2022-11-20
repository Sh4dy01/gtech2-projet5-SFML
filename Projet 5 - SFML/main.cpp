#define SFML_STATIC
#include <SFML/Graphics.hpp>

#include <Windows.h>
#include <gl/GL.h>


int main()
{
	sf::RenderWindow window(sf::VideoMode(640, 480), "Hey there!");

	while (window.isOpen())
	{
		// check all the window's events that were triggered since the last iteration of the loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// "close requested" event: we close the window
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		{
			glBegin(GL_TRIANGLES);
				glColor3f(1, 0, 0); glVertex3f(0.0F, 0.5F, 0.0F);
				glColor3f(0, 1, 0); glVertex3f(-0.5F, -0.5F, 0.0F);
				glColor3f(0, 0, 1); glVertex3f(0.5F, -0.5F, 0.0F);
			glEnd();
		}
		window.display();

		Sleep(1);
	}

	return 0;
}
