#pragma once
#include <iostream>
#include <SFML/Graphics/Sprite.hpp>

using namespace std;

class Tile : public sf::Sprite
{
public:

	Tile();

	//setters
	void          setPosX(int x);
	void          setPosY(int y);
	void          setIndex(int index);
	void          setFile(const string file);

	//getters
	int           getPosX();
	int           getPosy();
	int           getIndex();
	const string  getFile();

private:

	// name of the file where is the texture
	string file;

	// position in the file
	int posX;
	int posY;

	//index in atlas
	int index;
};
