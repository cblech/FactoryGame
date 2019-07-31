#pragma once
#include "GameObject.h"
#include <SFML\Graphics.hpp>

class GameMap;

class GmObjCar: public GameObject
{
public:
	GmObjCar();
	~GmObjCar();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void click(MapPixelCoor mousePosition) override;
	void clickStart(MapPixelCoor mousePosition) override;
	void clickEnd(MapPixelCoor mousePosition) override;

	void hoverStart(MapPixelCoor mousePosition)override;
	void hoverEnd(MapPixelCoor mousePosition)override;

	void holdStart(MapPixelCoor mousePosition)override;
	void holdEnd(MapPixelCoor mousePosition)override;

	void rightClick(MapPixelCoor mousePosition) override;

	nlohmann::json to_json() const override;
};

void from_json(const nlohmann::json& j, GmObjCar& p);