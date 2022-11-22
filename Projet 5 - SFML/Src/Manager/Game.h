#pragma once
#include <SFML/Graphics.hpp>

class Game {

public:
	
	static void Initialization();


public:

	static int GetWidth() { return width; };
	static int GetHeight() { return height; };


private:
	static sf::RenderWindow window;
	static int width;
	static int height;
};