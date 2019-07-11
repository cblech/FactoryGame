#include "GameObject.h"
#include "GameMap.h"

GameObject::GameObject(GameMap * map):containingMap(map),name("Generic GameObject")
{

}

GameObject::~GameObject()
{
	removeSpaceDependencies();
}

void GameObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

void GameObject::click(sf::Event::MouseButtonEvent mouseEvent)
{
}

void GameObject::hoverStart(sf::Vector2i mousePosition)
{
}

void GameObject::hoverEnd(sf::Vector2i mousePosition)
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

	for (int x = 0; x < size.x; x++)
	{
		if (tmpSpace == nullptr)
			break;
		Space * tmp2Space = tmpSpace;
		for (int y = 0; y < size.y; y++)
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

