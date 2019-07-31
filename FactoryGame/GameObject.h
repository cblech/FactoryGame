#pragma once
#include <SFML\Graphics.hpp>
#include "Space.h"
#include <vector>
#include <SFML\System.hpp>
#include "Coords.h"
#include "json.hpp"
#include <memory>

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
	GameObject();
	~GameObject();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void setGameMap(GameMap * map);

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

	virtual nlohmann::json to_json() const;

	void carrieTick(MapPixelCoor mousePosition); // Ticks every frame round, in witch this object is carried

	std::string getName();
	bool isMoveable() { return moveable; }

	void solveSpaceDependencies();
	void removeSpaceDependencies();

	void solvePosition(bool updateRotation = true);

	friend void from_json(const nlohmann::json& j, GameObject * p);
	friend void to_json(nlohmann::json& j, const GameObject& p);

protected:
	std::string name;

	bool moveable = false;
	bool carried = false;

	MapSpaceCoor position;
	MapSpaceCoor size;
	Direction pointing;

	MapPixelCoor moveingOffset; //while moveing this object, this variable carries the offset between the mouse and this objects origin.

	MapPixelCoor textureOffset; //the offset between the main/highlightSprite and the position of this GameObject

	std::shared_ptr<sf::Texture> mainTexture;
	sf::Sprite mainSprite;

	std::shared_ptr<sf::Texture> highlightTexture;
	sf::Sprite highlightSprite;

	std::vector<Space *> ocupiedSpaces; //The Spaces in the containingMap this GameObject ocupies
	GameMap * containingMap; //The map Containing this GameObject

private:
	void init();

};

Direction operator+(const Direction & left, const Direction & right);
void from_json(const nlohmann::json& j, GameObject * p);
void to_json(nlohmann::json& j,const GameObject& p);
void from_json(const nlohmann::json& j, Direction& p);
void to_json(nlohmann::json& j,const Direction& p);
