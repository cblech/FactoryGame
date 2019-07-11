#include "GmObjCar.h"
#include "GlobalDefines.h"
#include <iostream>

GmObjCar::GmObjCar(GameMap * map):GameObject(map)
{
	name = "Your Car";

	size.x = 4;
	size.y = 7;

	texture.loadFromFile("car.png");
	sprite.setTexture(texture);

	position.x = 5;
	position.y = 1;

	sprite.setPosition(position.x*spaceSizePX,position.y*spaceSizePX);

	
}


GmObjCar::~GmObjCar()
{
}

void GmObjCar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	
	target.draw(sprite, states);
}

void GmObjCar::click(sf::Event::MouseButtonEvent mouseEvent)
{
	std::cout << "Your Car: mouse click" << std::endl;
}

void GmObjCar::hoverStart(sf::Vector2i mousePosition)
{
	std::cout << "Your Car: mouse hover start" << std::endl;
}

void GmObjCar::hoverEnd(sf::Vector2i mousePosition)
{
	std::cout << "Your Car: mouse hover end" << std::endl;
}
