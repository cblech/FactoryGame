#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class GmObjCar: public GameObject
{
public:
	GmObjCar();
	~GmObjCar();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
};
