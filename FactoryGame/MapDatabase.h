#pragma once
#include "GameMap.h"
#include <vector>

class MapDatabase
{
public:
	MapDatabase(sf::RenderTarget * drawnIn, float pixelRatio);
	~MapDatabase();
	GameMap * getMap(unsigned int id);

private:
	std::vector<GameMap *> maps;
	sf::RenderTarget * drawnIn;
	float pixelRatio;
};

