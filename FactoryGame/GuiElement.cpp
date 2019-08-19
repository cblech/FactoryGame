#include "GuiElement.h"



GuiElement::GuiElement()
{
}


GuiElement::~GuiElement()
{
}

void GuiElement::solveSize()
{
}

bool GuiElement::containsLocal(OverlayLocalCoor point)
{
	
	return point.x>0&&point.y>0&&point.x<size.x&&point.y<size.y;
}

