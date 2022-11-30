#pragma once
#include "Manager/AnimatedEntity.h"
#include <iostream>
#include <string>
#include <vector>

class Tile;

class Map
{
public:
	Map();

	//render
	void				      render();

	// setters
	void					  setLength(int length);
	void					  setWidth(int width);
	void					  setName(std::string name);
	void					  setValue(int value, int x, int y);
	void					  setPosX(std::vector<int>&);
	void					  setPosY(std::vector<int>&);
	void					  setDir(std::vector<direction>&);
	void					  setEntityName(std::vector<std::string>&);
	void					  setType(std::vector<std::string>&);
	void					  setNbrEntity(int);

	// test de collision
	bool					  thereIsCollision(int x, int y);
		
	// getters
	int						  getLength();
	int						  getWidth();
	int						  getValue(int x, int y);
	int						  getNbrEntity();
	std::string&			  getName();
    std::vector<int>&         getPosX();
	std::vector<int>&         getPosY();
	std::vector<direction>&   getDir();
	std::vector<std::string>& getEntityName();
	std::vector<std::string>& getType();

private:

	std::string name;

	// dimensions of the map
	int length;
	int width;

	// Tab of pointer of Tile
	int tab[64][64];

	// manage entity
	int nbrEntity;
	std::vector<int> posX;
	std::vector<int> posY;
	std::vector<direction> dir;
	std::vector<std::string> entityName;
	std::vector<std::string> type;
};
