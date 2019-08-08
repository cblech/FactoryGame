#include "GuiButton.h"



GuiButton::GuiButton(sf::Vector2f size)
{
	this->size = size;
	backgroundShape.setSize(size);
	backgroundShape.setFillColor(BACKGROUND_COLOR);
}


GuiButton::~GuiButton()
{
}

void GuiButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
}

bool GuiButton::click(sf::Vector2f point)
{
	return false;
}
