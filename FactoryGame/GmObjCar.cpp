#include "GmObjCar.h"
#include "Global.h"
#include <iostream>
#include "Animation.h"
#include <SFML\System.hpp>

GmObjCar::GmObjCar()
{
	name = "Your Car";

	size.x = 4;
	size.y = 7;

	textureOffset = { -spaceSizePX,-spaceSizePX };

	mainTexture->loadFromFile("recources/car.png");
	highlightTexture->loadFromFile("recources/car_highlight.png");

	moveable = true;

	mainSprite.setTexture(*mainTexture);
	highlightSprite.setTexture(*highlightTexture);

}


GmObjCar::~GmObjCar()
{
}

void GmObjCar::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	GameObject::draw(target, states);
}


void GmObjCar::click(MapPixelCoor mousePosition)
{
	GameObject::click(mousePosition);

	std::cout << "Your Car: mouse click" << std::endl;
	auto a = std::make_shared<Animation<sf::Vector2f>>([this](sf::Vector2f v) {this->mainSprite.setScale(v); }, sf::Vector2f(2, 2), sf::Vector2f(1, 1), .5, Anim::Type::FastStart);
	Anim::ANIMATIONS.push_back(a);
}

void GmObjCar::clickStart(MapPixelCoor mousePosition)
{
	GameObject::clickStart(mousePosition);
	std::cout << "Your Car: mouse click start" << std::endl;
}

void GmObjCar::clickEnd(MapPixelCoor mousePosition)
{
	GameObject::clickEnd(mousePosition);
	std::cout << "Your Car: mouse click end" << std::endl;
}

void GmObjCar::hoverStart(MapPixelCoor mousePosition)
{
	GameObject::hoverStart(mousePosition);
	std::cout << "Your Car: mouse hover start" << std::endl;
}

void GmObjCar::hoverEnd(MapPixelCoor mousePosition)
{
	GameObject::hoverEnd(mousePosition);
	std::cout << "Your Car: mouse hover end" << std::endl;
}

void GmObjCar::holdStart(MapPixelCoor mousePosition)
{
	GameObject::holdStart(mousePosition);
	std::cout << "Your Car: mouse hold start" << std::endl;
}

void GmObjCar::holdEnd(MapPixelCoor mousePosition)
{
	GameObject::holdEnd(mousePosition);
	std::cout << "Your Car: mouse hold end" << std::endl;
}

void GmObjCar::rightClick(MapPixelCoor mousePosition)
{
	GameObject::rightClick(mousePosition);
	std::cout << "Your Car: mouse right click" << std::endl;
}

nlohmann::json GmObjCar::to_json() const
{
	json tj = GameObject::to_json();
	return json{
		{"gameobject", tj},
		{"type","GmObjCar"}
	};
}

void from_json(const nlohmann::json & j, GmObjCar & p)
{
	json tj = j["gameobject"];
	from_json(tj, &p);

}
//
//void my_to_json(nlohmann::json & j, const GmObjCar * p)
//{
//	json tj;
//	to_json(tj, &p);
//	j = json{
//		{"gameobject", tj},
//		{"type","GmObjCar"}
//	};
//}
