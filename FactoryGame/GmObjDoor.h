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

	void click(sf::Vector2i mousePosition) override;
	void hoverStart(sf::Vector2i mousePosition)override;
	void hoverEnd(sf::Vector2i mousePosition)override;
};
