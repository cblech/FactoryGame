#include "GameMap.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace nlohmann;

GameMap::GameMap(int id) :id(id)
{

}


GameMap::~GameMap()
{
	while (!spaces.empty())
	{
		Space * tmp = spaces.back();
		spaces.pop_back();
		delete tmp;
	}
}

void GameMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//draw the Background
	target.draw(backgroundSprite, states);
}

bool GameMap::initByFile(std::string filename)
{
	json j;
	try {
		std::ifstream i(filename);
		i >> j;
	}
	catch (...) {
		return false;
	}

	if (j["version"] == "FactoryGameMap0.1")
	{
		size.x = j["size"][0];
		size.y = j["size"][1];

		if (!backgroundTextrue.loadFromFile(j["background"]))
			return false;

		backgroundSprite.setTexture(backgroundTextrue);

		for (int y = 0; y < size.y; y++)
			for (int x = 0; x < size.x; x++)
			{
				Space * newSpace = new Space(x,y,j["walls"][y][x]);

				newSpace->left =getSpaceByCoord(x - 1, y);
				newSpace->above = getSpaceByCoord(x, y - 1);

				if (newSpace->left != nullptr)
					newSpace->left->right = newSpace;

				if (newSpace->above != nullptr)
					newSpace->above->below = newSpace;

				spaces.push_back(newSpace);
			}

	}
	else
		return false;


	return true;
}

inline GameMap::Space * GameMap::getSpaceByCoord(int x, int y) {
	for (auto & s : spaces)
	{
		if (s->coord.x == x && s->coord.y == y)
			return s;
	}
	return nullptr;
}

