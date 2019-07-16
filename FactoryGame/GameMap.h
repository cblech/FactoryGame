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

	GameMap(int id,sf::RenderTarget * drawnIn);
	~GameMap();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	MapPixelCoor ScreenPixelCoorTOMapPixelCoor(ScreenPixelCoor spc);
	ScreenPixelCoor MapPixelCoorTOScreenPixelCoor(MapPixelCoor mpc);

	MapSpaceCoor MapPixelCoorTOMapSpaceCoor(MapPixelCoor mpc);
	MapPixelCoor MapSpaceCoorTOMapPixelCoor(MapSpaceCoor msc);

	GmObjCar carlos; //Temporary
	GmObjDoor doory; //Temporary

	void setDrawnIn(sf::RenderTarget * rt);

	bool initByFile(std::string filename);
	void checkMousePosition(ScreenPixelCoor pos);
	void mouseClickEvent(sf::Event::MouseButtonEvent mouseEvent);
	void mouseReleaseEvent(sf::Event::MouseButtonEvent mouseEvent);
	friend void GameObject::solveSpaceDependencies();

	GameObject * carriedObject = nullptr;

	//Main Map Camera
	sf::View mapView;

	void emptyHoveringGameObject();

	bool checkForFreeSpaces(MapSpaceCoor from, MapSpaceCoor to,GameObject * self = nullptr);
	inline Space * getSpaceByMapSpaceCoor(int x, int y);
	inline Space * getSpaceByMapSpaceCoor(MapSpaceCoor pos);
private:


	int id;
	Type type;
	MapSpaceCoor size;
	sf::RenderTarget * drawnIn;

	std::vector<Space *> spaces;

	sf::Texture backgroundTextrue;
	sf::Sprite backgroundSprite;

	Space * mouseHoveringSpace;
	GameObject * hoveringGameObject;
	GameObject * holdingGameObject;
	bool holding;

	sf::Clock holdStartTime;
};

