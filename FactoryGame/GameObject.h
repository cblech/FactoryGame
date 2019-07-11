#pragma once
#include <SFML\Graphics.hpp>
//#include "GameMap.h"

class GameObject :public sf::Drawable
{
public:
	GameObject();
	~GameObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum Direction {
		up,
		down,
		left,
		right
	};

protected:
	sf::Vector2i position;
	sf::Vector2i size;
	Direction pointing;

	sf::Texture texture;
	sf::Sprite sprite;
};

