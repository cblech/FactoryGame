#pragma once
#include <SFML\System.hpp>
//#include "GameObject.h"

class GameObject;

enum SpaceType
{
	none = 0,
	wall = 1,
	object = 2
};

struct Space
{
	Space(int x, int y, int type)
	{
		coord.x = x;
		coord.y = y;
		spaceType = SpaceType(type);
	}
	sf::Vector2i coord; //The coordinates of this space
	SpaceType spaceType; //The type of this space (eg: none/air , wall , ...)

	GameObject * ocupiedBy = nullptr; //The GameObject ocupieing this space

	Space * above = nullptr; //The neighbor above this space
	Space * below = nullptr; //The neighbor below this space
	Space * left = nullptr; //The neighbor left to this space
	Space * right = nullptr; //The neighbor right to this space
};
