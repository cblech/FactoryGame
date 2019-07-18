#include "MapDatabase.h"



MapDatabase::MapDatabase(sf::RenderTarget * drawnIn, float pixelRatio): drawnIn(drawnIn),pixelRatio(pixelRatio)
{
}


MapDatabase::~MapDatabase()
{
	for (auto m : maps)
	{
		delete m;
	}
}

GameMap * MapDatabase::getMap(unsigned int id)
{
	if (id < maps.size())
	{
		if (maps[id] != nullptr)
		{
			return maps[id];
		}
	}
	else
	{
		maps.resize(id + 1);
	}
	GameMap * newMap = new GameMap(id,drawnIn,pixelRatio);
	switch (id)
	{
	case 1:
		if(!newMap->initByFile("garage.json"))
			return nullptr;
		break;
	case 2:
		if (!newMap->initByFile("shipyard.json"))
			return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
	maps[id] = newMap;

	return newMap;
}
