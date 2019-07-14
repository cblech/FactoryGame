#include "GameMap.h"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace nlohmann;

GameMap::GameMap(int id) :id(id),carlos(this),doory(this)
{
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

void GameMap::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	//draw the Background
	target.draw(backgroundSprite, states);
	target.draw(carlos, states);
	target.draw(doory, states);
}

bool GameMap::initByFile(std::string filename)
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
		size.x = j["size"][0];
		size.y = j["size"][1];

		if (!backgroundTextrue.loadFromFile(j["background"]))
			return false;

		backgroundSprite.setTexture(backgroundTextrue);

		for (int y = 0; y < size.y; y++)
			for (int x = 0; x < size.x; x++)
			{
				Space * newSpace = new Space(x,y,j["walls"][y][x]);

				newSpace->left =getSpaceByCoord(x - 1, y);
				newSpace->above = getSpaceByCoord(x, y - 1);

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


	return true;
}

void GameMap::checkMousePosition(sf::Vector2i pos)
{
	//std::cout <<"X: "<< (pos.x / spaceSizePX) << " Y: " << (pos.y / spaceSizePX)<<std::endl;

	Space * newSpace = getSpaceByCoord(pos.x / spaceSizePX, pos.y / spaceSizePX);

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
					hoveringGameObject->hoverEnd(pos);

				if (mouseHoveringSpace->ocupiedBy != nullptr)
					mouseHoveringSpace->ocupiedBy->hoverStart(pos);

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
		holdingGameObject->holdStart(pos);
		holding = true;
	}
}

//This function is executet, when any mousebutton is pressed
void GameMap::mouseClickEvent(sf::Event::MouseButtonEvent mouseEvent)
{
	//when the left mouse button is pressed
	if (mouseEvent.button == sf::Mouse::Button::Left) {
		if (hoveringGameObject != nullptr)
		{
			hoveringGameObject->clickStart({ mouseEvent.x,mouseEvent.y });

			holdStartTime.restart();
			holdingGameObject = hoveringGameObject;
		}
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
				holdingGameObject->holdEnd({ mouseEvent.x,mouseEvent.y });
				holding = false;
			}
			else
			{
				holdingGameObject->click({ mouseEvent.x,mouseEvent.y });
			}
			holdingGameObject->clickEnd({ mouseEvent.x,mouseEvent.y });
			holdingGameObject = nullptr;
		}
	}
}

inline Space * GameMap::getSpaceByCoord(int x, int y) {
	if (x < 0 || y < 0 || x >= size.x || y >= size.y)
		return nullptr;

	for (auto & s : spaces)
	{
		if (s->coord.x == x && s->coord.y == y)
			return s;
	}
	return nullptr;
}

