#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GmObjCar.h"
#include "GlobalDefines.h"
#include "Space.h"

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

	
	GmObjCar carlos; //Temporary


	bool initByFile(std::string filename);
	void checkMousePosition(sf::Vector2i pos);
	friend void GameObject::solveSpaceDependencies();


private:


	int id;
	Type type;
	sf::Vector2i size;

	std::vector<Space *> spaces;

	sf::Texture backgroundTextrue;
	sf::Sprite backgroundSprite;

	Space * mouseHoveringSpace;

	inline Space * getSpaceByCoord(int x, int y);
};

