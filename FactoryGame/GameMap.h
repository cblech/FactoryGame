#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GmObjCar.h"
#include "GlobalDefines.h"

class GameMap : public sf::Drawable
{
public:
	enum Type
	{
		noType,
		garage
	};

	GameMap(int id);
	~GameMap();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool initByFile(std::string filename);
	void checkMousePosition(sf::Vector2i pos);
private:
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

		Space * above = nullptr; //The neighbor above this space
		Space * below = nullptr; //The neighbor below this space
		Space * left = nullptr; //The neighbor left to this space
		Space * right = nullptr; //The neighbor right to this space
	};


	//Temporary
	GmObjCar carlos; 


	int id;
	Type type;
	sf::Vector2i size;

	std::vector<Space *> spaces;

	sf::Texture backgroundTextrue;
	sf::Sprite backgroundSprite;

	Space * mouseHoveringSpace;

	inline Space * getSpaceByCoord(int x, int y);


};

