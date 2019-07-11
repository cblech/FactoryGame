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

	void click(sf::Event::MouseButtonEvent mouseEvent) override;
	void hoverStart(sf::Vector2i mousePosition)override;
	void hoverEnd(sf::Vector2i mousePosition)override;
private:
};
