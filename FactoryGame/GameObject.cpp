#include "GameObject.h"
#include "GameMap.h"

GameObject::GameObject(GameMap * map):containingMap(map),name("Generic GameObject")
{

}

GameObject::~GameObject()
{
}

void GameObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{

	target.draw(sprite, states);
}

void GameObject::click(sf::Vector2i mousePosition)
{
}

void GameObject::clickStart(sf::Vector2i mousePosition)
{
}

void GameObject::clickEnd(sf::Vector2i mousePosition)
{
}

void GameObject::hoverStart(sf::Vector2i mousePosition)
{
}

void GameObject::hoverEnd(sf::Vector2i mousePosition)
{
}

void GameObject::holdStart(sf::Vector2i mousePosition)
{
}

void GameObject::holdEnd(sf::Vector2i mousePosition)
{
}

std::string GameObject::getName()
{
	return name;
}

void GameObject::solveSpaceDependencies()
{
	removeSpaceDependencies();
	Space * tmpSpace = containingMap->getSpaceByCoord(position.x, position.y);

	bool upOrDown = (pointing == Direction::down || pointing == Direction::up);
	int width = upOrDown ? size.x : size.y;
	int height = upOrDown ? size.y : size.x;

	for (int x = 0; x < width; x++)
	{
		if (tmpSpace == nullptr)
			break;
		Space * tmp2Space = tmpSpace;
		for (int y = 0; y < height; y++)
		{
			if (tmp2Space == nullptr)
				break;
			//position + sf::Vector2i(x, y);
			ocupiedSpaces.push_back(tmp2Space);
			tmp2Space->spaceType = SpaceType::object;
			tmp2Space->ocupiedBy = this;

			tmp2Space = tmp2Space->below;
		}
		tmpSpace = tmpSpace->right;
	}
}

void GameObject::removeSpaceDependencies()
{
	for (Space * s : ocupiedSpaces)
	{
		s->ocupiedBy = nullptr;
		s->spaceType = SpaceType::none;
	}
	ocupiedSpaces.clear();
}

void GameObject::solveRotation()
{
	switch (pointing)
	{
	case Direction::up:
		sprite.setRotation(0.f);
		sprite.setPosition(position.x*spaceSizePX, position.y*spaceSizePX);
		break;
	case Direction::down:
		sprite.setRotation(180.f);
		sprite.setPosition((position.x*spaceSizePX) + (size.x*spaceSizePX), (position.y*spaceSizePX) + (size.y*spaceSizePX));
		break;
	case Direction::left:
		sprite.setRotation(270.f);
		sprite.setPosition(position.x*spaceSizePX, (position.y*spaceSizePX) + (size.x*spaceSizePX));
		break;
	case Direction::right:
		sprite.setRotation(90.f);
		sprite.setPosition((position.x*spaceSizePX) + (size.y*spaceSizePX), position.y*spaceSizePX);
		break;
	}
	
}

