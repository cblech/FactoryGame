#include "GmObjDoor.h"
#include "GlobalDefines.h"
#include <iostream>
#include <SFML\System.hpp>

GmObjDoor::GmObjDoor(GameMap * map):GameObject(map)
{
	name = "Door";

	//the direction
	pointing = Direction::up;

	//size of the object
	size.x = 2;
	size.y = 1;

	//the main texture of the object
	texture.loadFromFile("door.png");
	
	//the position
	position.x = 3;
	position.y = 8;

	//Don't modify
	sprite.setTexture(texture);
	solvePosition();
}


GmObjDoor::~GmObjDoor()
{
}

//Drawing the Object
void GmObjDoor::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//Add something under the default drawing
	
	GameObject::draw(target, states); //Default drawing
	
	//Add something above the default drawing
}

//Executes, when Object is Clicked
void GmObjDoor::click(sf::Vector2i mousePosition)
{
	std::cout << getName()<< ": mouse click" << std::endl;
}

//Executes, when Mouse starts hovering the Object
void GmObjDoor::hoverStart(sf::Vector2i mousePosition)
{
	std::cout << getName() << ": mouse hover start" << std::endl;
}

//Executes, when Mouse stops hovering the Object
void GmObjDoor::hoverEnd(sf::Vector2i mousePosition)
{
	std::cout << getName() << ": mouse hover end" << std::endl;
}

