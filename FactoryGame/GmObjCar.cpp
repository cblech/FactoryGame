#include "GmObjCar.h"
#include "GlobalDefines.h"

GmObjCar::GmObjCar()
{
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
