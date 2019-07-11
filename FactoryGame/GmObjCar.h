#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class GameMap;

class GmObjCar: public GameObject
{
public:
	GmObjCar(GameMap * map);
	~GmObjCar();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
};
