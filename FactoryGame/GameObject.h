#pragma once
#include <SFML\Graphics.hpp>
#include "Space.h"
#include <vector>

class GameMap;

class GameObject :public sf::Drawable
{
public:
	GameObject(GameMap * map);
	~GameObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	enum Direction {
		up,
		down,
		left,
		right
	};

	std::string getName();


	void solveSpaceDependencies();
	void removeSpaceDependencies();

protected:
	std::string name;

	sf::Vector2i position;
	sf::Vector2i size;
	Direction pointing;

	sf::Texture texture;
	sf::Sprite sprite;

	GameMap * containingMap; //The map Containing this GameObject
	std::vector<Space *> ocupiedSpaces; //The Spaces in the containingMap this GameObject ocupies

};

