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

GameMap * MapDatabase::getMap(unsigned int id, nlohmann::json savedObjects)
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
	GameMap * newMap = new GameMap(id, drawnIn, pixelRatio);
	newMap->zoomCamera(0);


	switch (id)
	{
	case 1:
		if(!newMap->initByFile("recources/garage.json", savedObjects["garage"]))
			return nullptr;
		break;
	case 2:
		if (!newMap->initByFile("recources/shipyard.json", savedObjects["shipyard"]))
			return nullptr;
		break;
	default:
		return nullptr;
		break;
	}
	maps[id] = newMap;

	//Temp
	//newMap->doory.solveSpaceDependencies();
	//newMap->carlos.solveSpaceDependencies();

	return newMap;
}

std::vector<GameMap*> MapDatabase::getLoadedMaps()
{
	std::vector<GameMap*> retval;
	for (auto * m : maps)
	{
		if (m != nullptr)
			retval.push_back(m);
	}
	return retval;
}
