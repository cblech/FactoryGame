#include "GameMap.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include "Clamp.h"

using namespace nlohmann;

GameMap::GameMap(int id, sf::RenderTarget * drawnIn, float pixelRatio) :id(id),drawnIn(drawnIn),pixelRatio(pixelRatio)
{
	//mapView.reset({ 0,0,1280,720 });
	//objects.push_back(&doory);
	//objects.push_back(&carlos);


}


GameMap::~GameMap()
{
	while (!spaces.empty())
	{
		Space * tmp = spaces.back();
		spaces.pop_back();
		delete tmp;
	}
}

int GameMap::getID()
{
	return id;
}

std::string GameMap::getName()
{
	return name;
}

std::string GameMap::getDescription()
{
	return description;
}

std::vector<GameObject*> GameMap::getObjects()
{
	return objects;
}

void GameMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//draw the Background
	target.draw(backgroundSprite,states);
	for (auto * o : objects)
	{
		target.draw(*o, states);
	}
	//target.draw(doory, states);
	//target.draw(carlos, states);
}

MapPixelCoor GameMap::ScreenPixelCoorTOMapPixelCoor(ScreenPixelCoor spc)
{
	return drawnIn->mapPixelToCoords(spc);
}

ScreenPixelCoor GameMap::MapPixelCoorTOScreenPixelCoor(MapPixelCoor mpc)
{
	return drawnIn->mapCoordsToPixel(mpc);
}

MapSpaceCoor GameMap::MapPixelCoorTOMapSpaceCoor(MapPixelCoor mpc)
{
	return MapSpaceCoor(mpc/float(spaceSizePX));
}

MapPixelCoor GameMap::MapSpaceCoorTOMapPixelCoor(MapSpaceCoor msc)
{
	return MapPixelCoor(msc*spaceSizePX);
}

void GameMap::setDrawnIn(sf::RenderTarget * rt)
{
	drawnIn = rt;
}

bool GameMap::initByFile(std::string filename, nlohmann::json objs)
{
	json j;
	try {
		std::ifstream i(filename);
		i >> j;
	}
	catch (...) {
		return false;
	}

	if (j["version"] == "FactoryGameMap0.1")
	{
		name = j["name"].get<std::string>();
		description = j["description"].get<std::string>();

		size.x = j["size"][0];
		size.y = j["size"][1];

		if (!backgroundTextrue.loadFromFile(j["background"]))
			return false;

		backgroundSprite.setTexture(backgroundTextrue);

		for (int y = 0; y < size.y; y++)
			for (int x = 0; x < size.x; x++)
			{
				Space * newSpace = new Space(x, y, j["walls"][y][x]);

				newSpace->left = getSpaceByMapSpaceCoor(x - 1, y);
				newSpace->above = getSpaceByMapSpaceCoor(x, y - 1);

				if (newSpace->left != nullptr)
					newSpace->left->right = newSpace;

				if (newSpace->above != nullptr)
					newSpace->above->below = newSpace;

				spaces.push_back(newSpace);
			}

		if (j["type"] == "garage")
			type = Type::garage;
		else
			type = Type::noType;

	}
	else
		return false;

	//createObjects

	for (json o : objs)
	{
		GameObject * newObject = nullptr;
		const std::string oType = o["type"].get<std::string>();
		if (oType == "GmObjCar")
		{
			GmObjCar nO = o;
			nO.setGameMap(this);
			newObject = new GmObjCar(nO);
			newObject->solvePosition();
			newObject->solveSpaceDependencies();
			objects.push_back(newObject);
		}
		
	}

	return true;
}

void GameMap::checkMousePosition(ScreenPixelCoor pos)
{
	//std::cout <<"X: "<< (pos.x / spaceSizePX) << " Y: " << (pos.y / spaceSizePX)<<std::endl;

	Space * newSpace = getSpaceByMapSpaceCoor(MapPixelCoorTOMapSpaceCoor(ScreenPixelCoorTOMapPixelCoor(pos)));

	if (newSpace != mouseHoveringSpace) 
	{
		mouseHoveringSpace = newSpace;

		if (mouseHoveringSpace != nullptr)
		{
			//Executes When mouse goes to a nother Space

			if (mouseHoveringSpace->ocupiedBy != hoveringGameObject)
			{
				//Executes when mouse switches from or to an GameObject

				if (hoveringGameObject != nullptr)
					hoveringGameObject->hoverEnd(ScreenPixelCoorTOMapPixelCoor(pos));

				if (mouseHoveringSpace->ocupiedBy != nullptr)
					mouseHoveringSpace->ocupiedBy->hoverStart(ScreenPixelCoorTOMapPixelCoor(pos));

				hoveringGameObject = mouseHoveringSpace->ocupiedBy;
			}

/*
			switch (mouseHoveringSpace->spaceType)
			{
			case SpaceType::none:
				std::cout << "Air" << std::endl;
				break;
			case SpaceType::wall:
				std::cout << "Wall" << std::endl;
				break;
			case SpaceType::object:
				std::cout << "Object: " << mouseHoveringSpace->ocupiedBy->getName() <<std::endl;
				break;
			default:
				std::cout << "Dafuq? Wie bist du hier hin gekommen??" << std::endl;
				break;
			}*/
		}
	}
	
	//Handle mouse hold events
	if (!holding && holdingGameObject != nullptr && holdingGameObject==hoveringGameObject && holdStartTime.getElapsedTime() > sf::milliseconds(500))
	{
		holdingGameObject->holdStart(ScreenPixelCoorTOMapPixelCoor(pos));
		holding = true;
	}

	//nedes to do stuff when an Object is Carreid
	if (carriedObject != nullptr)
	{
		carriedObject->carrieTick(ScreenPixelCoorTOMapPixelCoor(pos));
	}

	//Stuff for Window dragging 
	if (cameraIsDraged)
	{
		moveCamera(mousePositionWhileDragged-ScreenPixelCoorTOMapPixelCoor(pos));
		//mousePositionWhileDragged = ScreenPixelCoorTOMapPixelCoor(pos);
	}
}

//This function is executet, when any mousebutton is pressed
void GameMap::mouseClickEvent(sf::Event::MouseButtonEvent mouseEvent)
{
	//when the LEFT mouse button is pressed
	if (mouseEvent.button == sf::Mouse::Button::Left) {
		if (hoveringGameObject != nullptr)
		{
			hoveringGameObject->clickStart(ScreenPixelCoorTOMapPixelCoor({ mouseEvent.x,mouseEvent.y }));

			holdStartTime.restart();
			holdingGameObject = hoveringGameObject;
		}
	}
	//when the RIGHT mouse button is pressed
	else if (mouseEvent.button == sf::Mouse::Button::Right)
	{
		if (carriedObject != nullptr)
		{
			carriedObject->rightClick(ScreenPixelCoorTOMapPixelCoor({ mouseEvent.x,mouseEvent.y }));
		}
		else if(hoveringGameObject != nullptr)
			hoveringGameObject->rightClick(ScreenPixelCoorTOMapPixelCoor({ mouseEvent.x,mouseEvent.y }));

		//mapView.rotate(30.f);
	}
	//start dragging Camera
	else if (mouseEvent.button == sf::Mouse::Button::Middle)
	{
		cameraIsDraged = true;
		mousePositionWhileDragged = ScreenPixelCoorTOMapPixelCoor({ mouseEvent.x,mouseEvent.y });
	}

}

//This function is executet, when any mousebutton is released
void GameMap::mouseReleaseEvent(sf::Event::MouseButtonEvent mouseEvent)
{
	//When the left mouse button is released
	if (mouseEvent.button == sf::Mouse::Button::Left) {
		if (holdingGameObject != nullptr)
		{
			if (holding)
			{
				holdingGameObject->holdEnd(ScreenPixelCoorTOMapPixelCoor({ mouseEvent.x,mouseEvent.y }));
				holding = false;
			}
			else
			{
				holdingGameObject->click(ScreenPixelCoorTOMapPixelCoor({ mouseEvent.x,mouseEvent.y }));
			}
			holdingGameObject->clickEnd(ScreenPixelCoorTOMapPixelCoor({ mouseEvent.x,mouseEvent.y }));
			holdingGameObject = nullptr;
		}
	}
	else if (mouseEvent.button == sf::Mouse::Button::Middle)
	{
		cameraIsDraged = false;
	}
}

sf::View GameMap::getMapView()
{
	return mapView;
}

void GameMap::setMapView(sf::View view)
{
	mapView = view;
	zoomCamera(0);
}

void GameMap::moveCamera(Direction dir, double delta)
{
	const double movementspeed = double(zoomLevel*zoomLevel) ;
	switch (dir)
	{
	case up:
		moveCamera(MapPixelCoor(0,-movementspeed*delta));
		break;
	case right:
		moveCamera(MapPixelCoor(movementspeed * delta, 0));
		break;
	case down:
		moveCamera(MapPixelCoor(0, movementspeed * delta));
		break;
	case left:
		moveCamera(MapPixelCoor(-movementspeed * delta, 0));
		break;
	default:
		break;
	}
}

void GameMap::moveCamera(MapPixelCoor offset)
{
	mapView.move(offset);
}

void GameMap::zoomCamera(double delta)
{
	zoomLevel -= delta * zoomSpeed;
	zoomLevel = clamp<int>(zoomLevel, minZoomLevel, maxZoomLevel);

	mapView.setSize(zoomLevel*zoomLevel*pixelRatio, zoomLevel*zoomLevel);
}

void GameMap::setPixelRatio(float ratio)
{
	pixelRatio = ratio;
}

void GameMap::setDrawIn(sf::RenderTarget * drawIn)
{
	this->drawnIn = drawIn;
}

void GameMap::emptyHoveringGameObject()
{
	hoveringGameObject = nullptr;
	mouseHoveringSpace = nullptr;
}

bool GameMap::checkForFreeSpaces(MapSpaceCoor from, MapSpaceCoor to,GameObject * self)
{
	MapSpaceCoor topLeft((from.x < to.x) ? from.x : to.x, (from.y < to.y) ? from.y : to.y);
	MapSpaceCoor bottomRight((from.x > to.x) ? from.x : to.x, (from.y > to.y) ? from.y : to.y);

	int width = bottomRight.x - topLeft.x;
	int height = bottomRight.y - topLeft.y;

	Space * testSpace = getSpaceByMapSpaceCoor(topLeft);

	for (int x = 0; x < width; x++)
	{
		if (testSpace == nullptr)
			return false;
		Space * tmpSpace = testSpace;
		for (int y = 0; y < height; y++)
		{
			if (tmpSpace == nullptr)
				return false;
			if (tmpSpace->spaceType != SpaceType::none)
				if (!(tmpSpace->spaceType == SpaceType::object && tmpSpace->ocupiedBy == self))
					return false;
					
			tmpSpace = tmpSpace->below;
		}
		testSpace = testSpace->right;
	}
	return true;
}

inline Space * GameMap::getSpaceByMapSpaceCoor(int x, int y) {
	if (x < 0 || y < 0 || x >= size.x || y >= size.y)
		return nullptr;

	for (auto & s : spaces)
	{
		if (s->coord.x == x && s->coord.y == y)
			return s;
	}
	return nullptr;
}

inline Space * GameMap::getSpaceByMapSpaceCoor(MapSpaceCoor pos)
{
	return getSpaceByMapSpaceCoor(pos.x,pos.y);
}

void GameMap::solveObjectsMap()
{
	for (auto o : objects) 
	{
		o->setGameMap(this);
	}
}

