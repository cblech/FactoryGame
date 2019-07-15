#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "GmObjCar.h"
#include "GlobalDefines.h"
#include "Space.h"
#include "GmObjDoor.h"

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
	GmObjDoor doory; //Temporary


	bool initByFile(std::string filename);
	void checkMousePosition(sf::Vector2i pos);
	void mouseClickEvent(sf::Event::MouseButtonEvent mouseEvent);
	void mouseReleaseEvent(sf::Event::MouseButtonEvent mouseEvent);
	friend void GameObject::solveSpaceDependencies();

	GameObject * carriedObject = nullptr;

	//Main Map Camera
	sf::View mapView;

	void emptyHoveringGameObject();

	bool checkForFreeSpaces(sf::Vector2i from, sf::Vector2i to,GameObject * self = nullptr);
	inline Space * getSpaceByCoord(int x, int y);
	inline Space * getSpaceByCoord(sf::Vector2i pos);
private:


	int id;
	Type type;
	sf::Vector2i size;

	std::vector<Space *> spaces;

	sf::Texture backgroundTextrue;
	sf::Sprite backgroundSprite;

	Space * mouseHoveringSpace;
	GameObject * hoveringGameObject;
	GameObject * holdingGameObject;
	bool holding;

	sf::Clock holdStartTime;
};

