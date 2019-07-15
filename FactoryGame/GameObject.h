#pragma once
#include <SFML\Graphics.hpp>
#include "Space.h"
#include <vector>
#include <SFML\System.hpp>

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


	//events
	virtual void click(sf::Vector2i mousePosition);
	virtual void clickStart(sf::Vector2i mousePosition);
	virtual void clickEnd(sf::Vector2i mousePosition);

	virtual void hoverStart(sf::Vector2i mousePosition);
	virtual void hoverEnd(sf::Vector2i mousePosition);

	virtual void holdStart(sf::Vector2i mousePosition);
	virtual void holdEnd(sf::Vector2i mousePosition);
	
	virtual void rightClick(sf::Vector2i mousePosition);

	void carrieTick(sf::Vector2i mousePosition);

	std::string getName();
	bool isMoveable() { return moveable; }

	void solveSpaceDependencies();
	void removeSpaceDependencies();

protected:
	std::string name;

	bool moveable = false;
	bool carried = false;

	sf::Vector2i position;
	sf::Vector2i size;
	Direction pointing;

	sf::Vector2i moveingOffset;

	sf::Texture texture;
	sf::Sprite sprite;

	sf::Texture highlightTexture;
	sf::Sprite highlightSprite;

	std::vector<Space *> ocupiedSpaces; //The Spaces in the containingMap this GameObject ocupies
	GameMap * containingMap; //The map Containing this GameObject

	void solvePosition(bool updateRotation = true);

};

