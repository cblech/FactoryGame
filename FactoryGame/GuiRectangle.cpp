#include "GuiRectangle.h"
#include <iostream>




GuiRectangle::GuiRectangle(sf::Vector2f size, sf::Color color)
{
	this->size = size;
	rec.setSize(size);
	rec.setFillColor(color);
}

GuiRectangle::~GuiRectangle()
{
}

void GuiRectangle::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(rec, states);
}

bool GuiRectangle::click(sf::Vector2f point)
{
	if (!containsLocal(point))
		return false;
	std::cout << "Rectangle Click" << std::endl;
	return true;
}
