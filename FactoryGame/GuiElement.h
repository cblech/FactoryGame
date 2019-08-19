#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include "Coords.h"

#define BACKGROUND_COLOR sf::Color(180, 180, 255, 255)

class GuiElement:public sf::Drawable 
{
public:
	GuiElement();
	~GuiElement();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;


	virtual void solveSize();

	//virtual bool click(sf::Vector2f point) = 0;
	sf::Vector2f size;

	sf::Transform totalTransform;

protected:
	bool containsLocal(OverlayLocalCoor point);

	
};

typedef std::shared_ptr<GuiElement> GuiElementPtr;
