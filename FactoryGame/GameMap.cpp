#include "GameMap.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace nlohmann;

GameMap::GameMap(int id):id(id)
{

}


GameMap::~GameMap()
{
}

void GameMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
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
	}
	else
		return false;


	return true;
}
