#include "GameObject.h"
#include "GameMap.h"

#define COLOR_TRANSPARENT sf::Color::Transparent
#define COLOR_HL_HOVER sf::Color(0,0,0,80)
#define COLOR_HL_POSITIVE sf::Color(0,150,0,180)
#define COLOR_HL_NEGATIVE sf::Color(150,0,0,180)
#define COLOR_TX_CARRY sf::Color(255,255,255,200)
#define COLOR_TX_FULLYVISIBLE sf::Color::White

GameObject::GameObject(GameMap * map) :containingMap(map), name("Generic GameObject")
{
	highlightSprite.setColor(COLOR_TRANSPARENT);
}

GameObject::~GameObject()
{
}

void GameObject::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(highlightSprite, states);
	target.draw(mainSprite, states);
}

void GameObject::click(MapPixelCoor mousePosition)
{
}

void GameObject::clickStart(MapPixelCoor mousePosition)
{
}

void GameObject::clickEnd(MapPixelCoor mousePosition)
{
}

void GameObject::hoverStart(MapPixelCoor mousePosition)
{
	if(!carried)
		highlightSprite.setColor(COLOR_HL_HOVER);
}

void GameObject::hoverEnd(MapPixelCoor mousePosition)
{
	if(!carried)
		highlightSprite.setColor(COLOR_TRANSPARENT);
}

void GameObject::holdStart(MapPixelCoor mousePosition)
{
	if (isMoveable())
	{
		carried = true;
		moveingOffset = MapPixelCoor(mainSprite.getPosition()-textureOffset) - mousePosition;
		containingMap->carriedObject = this;
		mainSprite.setColor(COLOR_TX_CARRY);
	}
}

void GameObject::holdEnd(MapPixelCoor mousePosition)
{
	if (carried)
	{
		carried = false;
		containingMap->carriedObject = nullptr;

		solvePosition(false);
		mainSprite.setColor(COLOR_TX_FULLYVISIBLE);
		highlightSprite.setColor(COLOR_TRANSPARENT);

		containingMap->emptyHoveringGameObject();


		MapSpaceCoor carriedOverSpace = containingMap->MapPixelCoorTOMapSpaceCoor((mousePosition + moveingOffset) + MapPixelCoor(spaceSizePX / 2, spaceSizePX / 2));
		if (containingMap->checkForFreeSpaces(carriedOverSpace, carriedOverSpace + size, this))
		{
			position = carriedOverSpace;
			solveSpaceDependencies();
			solvePosition(false);
		}

	}
}

void GameObject::rightClick(MapPixelCoor mousePosition)
{
	
}

void GameObject::carrieTick(MapPixelCoor mousePosition)
{
	
	MapSpaceCoor carriedOverSpace = containingMap->MapPixelCoorTOMapSpaceCoor((mousePosition + moveingOffset) + MapPixelCoor(spaceSizePX / 2, spaceSizePX / 2));

	//Check if placeable
	if (containingMap->checkForFreeSpaces(carriedOverSpace, carriedOverSpace + size,this))
	{
		highlightSprite.setColor(COLOR_HL_POSITIVE);
		mainSprite.setPosition(sf::Vector2f(carriedOverSpace*spaceSizePX)+textureOffset);
		highlightSprite.setPosition(sf::Vector2f(carriedOverSpace*spaceSizePX)+textureOffset);
	}
	else
	{
		highlightSprite.setColor(COLOR_HL_NEGATIVE);
		mainSprite.setPosition(sf::Vector2f(mousePosition + moveingOffset)+textureOffset);
		highlightSprite.setPosition(sf::Vector2f(mousePosition + moveingOffset)+textureOffset);
	}
}

std::string GameObject::getName()
{
	return name;
}

void GameObject::solveSpaceDependencies()
{
	removeSpaceDependencies();
	Space * tmpSpace = containingMap->getSpaceByMapSpaceCoor(position.x, position.y);

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

void GameObject::solvePosition(bool updateRotation)
{
	switch (pointing)
	{
	case Direction::up:
		if (updateRotation)
		{
			mainSprite.setRotation(0.f);
			highlightSprite.setRotation(0.f);
		}
		mainSprite.setPosition(containingMap->MapSpaceCoorTOMapPixelCoor(position)+textureOffset);
		highlightSprite.setPosition(sf::Vector2f(position*spaceSizePX) + textureOffset);
		break;
	
	/*case Direction::down:
		if (updateRotation)
		{
			mainSprite.setRotation(180.f);
			highlightSprite.setRotation(180.f);
		}
		mainSprite.setPosition((position.x*spaceSizePX) + (size.x*spaceSizePX), (position.y*spaceSizePX) + (size.y*spaceSizePX));
		highlightSprite.setPosition((position.x*spaceSizePX) + (size.x*spaceSizePX), (position.y*spaceSizePX) + (size.y*spaceSizePX));
		break;
	case Direction::left:
		if (updateRotation)
		{
			mainSprite.setRotation(270.f);
			highlightSprite.setRotation(270.f);
		}
		mainSprite.setPosition(position.x*spaceSizePX, (position.y*spaceSizePX) + (size.x*spaceSizePX));
		highlightSprite.setPosition(position.x*spaceSizePX, (position.y*spaceSizePX) + (size.x*spaceSizePX));
		break;
	case Direction::right:
		if (updateRotation)
		{
			mainSprite.setRotation(90.f);
			highlightSprite.setRotation(90.f);
		}
		mainSprite.setPosition((position.x*spaceSizePX) + (size.y*spaceSizePX), position.y*spaceSizePX);
		highlightSprite.setPosition((position.x*spaceSizePX) + (size.y*spaceSizePX), position.y*spaceSizePX);
		break;*/
	}

}

Direction operator+(const Direction & left, const Direction & right)
{
	return Direction((int(left) + int(right)) % 4);
}
