#include "GmObjCar.h"
#include "GlobalDefines.h"
#include <iostream>
#include "Animation.h"
#include <SFML\System.hpp>

GmObjCar::GmObjCar(GameMap * map):GameObject(map)
{
	name = "Your Car";

	pointing = Direction::up;

	size.x = 4;
	size.y = 7;

	texture.loadFromFile("car.png");
	sprite.setTexture(texture);

	position.x = 5;
	position.y = 1;

	

	solveRotation();
}


GmObjCar::~GmObjCar()
{
}

void GmObjCar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	GameObject::draw(target, states);
}


void GmObjCar::click(sf::Vector2i mousePosition)
{

	std::cout << "Your Car: mouse click" << std::endl;
	auto a = std::make_shared<Animation<sf::Vector2f>>([this](sf::Vector2f v) {this->sprite.setScale(v); }, sf::Vector2f (2,2), sf::Vector2f(1,1), .5,  Anim::Type::FastStart);
	Anim::ANIMATIONS.push_back(a);
}

void GmObjCar::clickStart(sf::Vector2i mousePosition)
{
	std::cout << "Your Car: mouse click start" << std::endl;
}

void GmObjCar::clickEnd(sf::Vector2i mousePosition)
{
	std::cout << "Your Car: mouse click end" << std::endl;
}

void GmObjCar::hoverStart(sf::Vector2i mousePosition)
{
	std::cout << "Your Car: mouse hover start" << std::endl;
}

void GmObjCar::hoverEnd(sf::Vector2i mousePosition)
{
	std::cout << "Your Car: mouse hover end" << std::endl;
}

void GmObjCar::holdStart(sf::Vector2i mousePosition)
{
	std::cout << "Your Car: mouse hold start" << std::endl;
}

void GmObjCar::holdEnd(sf::Vector2i mousePosition)
{
	std::cout << "Your Car: mouse hold end" << std::endl;
}
