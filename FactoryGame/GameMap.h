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

	GameMap(int id, sf::RenderTarget * drawnIn, float pixelRatio);
	~GameMap();

	int getID();
	std::string getName();
	std::string getDescription();

	std::vector<GameObject *> getObjects();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	MapPixelCoor ScreenPixelCoorTOMapPixelCoor(ScreenPixelCoor spc);
	ScreenPixelCoor MapPixelCoorTOScreenPixelCoor(MapPixelCoor mpc);

	MapSpaceCoor MapPixelCoorTOMapSpaceCoor(MapPixelCoor mpc);
	MapPixelCoor MapSpaceCoorTOMapPixelCoor(MapSpaceCoor msc);

	//GmObjCar carlos; //Temporary
	//GmObjDoor doory; //Temporary

	void setDrawnIn(sf::RenderTarget * rt);

	bool initByFile(std::string filename,nlohmann::json objs);
	void checkMousePosition(ScreenPixelCoor pos);
	void mouseClickEvent(sf::Event::MouseButtonEvent mouseEvent);
	void mouseReleaseEvent(sf::Event::MouseButtonEvent mouseEvent);
	friend void GameObject::solveSpaceDependencies();

	GameObject * carriedObject = nullptr;

	//Main Map Camera
	sf::View mapView;

	sf::View getMapView();
	void setMapView(sf::View view);
	void moveCamera(Direction dir, double delta);
	void moveCamera(MapPixelCoor offset);
	void zoomCamera(double delta);
	void setPixelRatio(float ratio);

	void setDrawIn(sf::RenderTarget * drawIn);
	//Spaces
	void emptyHoveringGameObject();

	bool checkForFreeSpaces(MapSpaceCoor from, MapSpaceCoor to,GameObject * self = nullptr);
	inline Space * getSpaceByMapSpaceCoor(int x, int y);
	inline Space * getSpaceByMapSpaceCoor(MapSpaceCoor pos);
	void solveObjectsMap();

private:
	int id;
	std::string name;
	std::string description;
	Type type;
	MapSpaceCoor size;
	sf::RenderTarget * drawnIn;
	std::vector<GameObject *> objects;

	std::vector<Space *> spaces;

	sf::Texture backgroundTextrue;
	sf::Sprite backgroundSprite;


	//Main Map Camera
	
	float pixelRatio;
	int zoomLevel = 27;
	int zoomSpeed = 3;
	int maxZoomLevel = 100;
	int minZoomLevel = 21;

	bool cameraIsDraged = false;
	MapPixelCoor mousePositionWhileDragged;

	//Spaces
	Space * mouseHoveringSpace;
	GameObject * hoveringGameObject;
	GameObject * holdingGameObject;
	bool holding;

	sf::Clock holdStartTime;
};
