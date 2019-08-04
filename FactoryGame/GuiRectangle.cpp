#include "GuiRectangle.h"





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
