#pragma once
#include<SFML\Graphics.hpp>

class GameMap: public sf::Drawable
{
public:
	GameMap();
	~GameMap();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

