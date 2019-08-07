#pragma once
#include "GuiElement.h"
class GuiRectangle :public GuiElement
{
public:
	GuiRectangle(sf::Vector2f size,sf::Color color);
	~GuiRectangle();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual bool click(sf::Vector2f point);
private:
	sf::RectangleShape rec;
};

#define GUI_SPACE(s) std::make_shared<GuiRectangle>(sf::Vector2f{s,s}, sf::Color::Transparent) 
