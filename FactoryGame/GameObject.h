#pragma once
#include <SFML\Graphics.hpp>
#include "Space.h"
#include <vector>
#include <SFML\System.hpp>
#include "Coords.h"

class GameMap;

enum Direction {
	up = 0,
	right = 1,
	down = 2,
	left = 3
};

class GameObject :public sf::Drawable
{
public:
	GameObject(GameMap * map);
	~GameObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;




	//events
	virtual void click(MapPixelCoor mousePosition);
	virtual void clickStart(MapPixelCoor mousePosition);
	virtual void clickEnd(MapPixelCoor mousePosition);

	virtual void hoverStart(MapPixelCoor mousePosition);
	virtual void hoverEnd(MapPixelCoor mousePosition);

	virtual void holdStart(MapPixelCoor mousePosition);
	virtual void holdEnd(MapPixelCoor mousePosition);
	
	virtual void rightClick(MapPixelCoor mousePosition);
	//events - END

	void carrieTick(MapPixelCoor mousePosition); // Ticks every frame round, in witch this object is carried

	std::string getName();
	bool isMoveable() { return moveable; }

	void solveSpaceDependencies();
	void removeSpaceDependencies();

protected:
	std::string name;

	bool moveable = false;
	bool carried = false;

	MapSpaceCoor position;
	MapSpaceCoor size;
	Direction pointing;

	MapPixelCoor moveingOffset; //while moveing this object, this variable carries the offset between the mouse and this objects origin.

	MapPixelCoor textureOffset; //the offset between the main/highlightSprite and the position of this GameObject

	sf::Texture mainTexture;
	sf::Sprite mainSprite;

	sf::Texture highlightTexture;
	sf::Sprite highlightSprite;

	std::vector<Space *> ocupiedSpaces; //The Spaces in the containingMap this GameObject ocupies
	GameMap * containingMap; //The map Containing this GameObject

	void solvePosition(bool updateRotation = true);

};

Direction operator+(const Direction & left, const Direction & right);

