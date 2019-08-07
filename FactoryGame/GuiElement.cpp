#include "GuiElement.h"



GuiElement::GuiElement()
{
}


GuiElement::~GuiElement()
{
}

bool GuiElement::containsLocal(sf::Vector2f point)
{
	
	return point.x>0&&point.y>0&&point.x<size.x&&point.y<size.y;
}

