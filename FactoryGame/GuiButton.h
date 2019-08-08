#pragma once
#include "GuiElement.h"
class GuiButton : public GuiElement
{
public:
	GuiButton(sf::Vector2f size);
	~GuiButton();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	virtual bool click(sf::Vector2f point);
private:

	sf::RectangleShape backgroundShape;
};

