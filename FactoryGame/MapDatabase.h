#pragma once
#include "GameMap.h"
#include <vector>
#include "json.hpp"

class MapDatabase
{
public:
	MapDatabase(sf::RenderTarget * drawnIn, float pixelRatio);
	~MapDatabase();
	GameMap * getMap(unsigned int id, nlohmann::json savedObjects);
	std::vector<GameMap *> getLoadedMaps();

private:
	std::vector<GameMap *> maps;
	sf::RenderTarget * drawnIn;
	float pixelRatio;
};

