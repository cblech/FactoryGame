#pragma once
#include <SFML/System.hpp>
#include "GuiElement.h"
class GuiRectangle :	public GuiElement
{
public:
	GuiRectangle(sf::Vector2f size,sf::Color color);
	~GuiRectangle();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
private:
	sf::RectangleShape rec;
};

#define GUI_SPACE(s) std::make_shared<GuiRectangle>(sf::Vector2f{s,s}, sf::Color::Transparent) 
