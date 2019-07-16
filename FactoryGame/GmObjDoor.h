#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class GameMap;

class GmObjDoor : public GameObject
{
public:
	GmObjDoor(GameMap * map);
	~GmObjDoor();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void click(MapPixelCoor mousePosition) override;
	void hoverStart(MapPixelCoor mousePosition) override;
	void hoverEnd(MapPixelCoor mousePosition) override;
};
