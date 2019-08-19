#include "GuiButton.h"
#include <iostream>


GuiButton::GuiButton(sf::Vector2f size)
{
	this->size = size;
	backgroundShape.setSize(size);
	backgroundShape.setFillColor(sf::Color::White);

	setBounds(backgroundShape.getGlobalBounds());
}


GuiButton::~GuiButton()
{
}

void GuiButton::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(backgroundShape, states);
}

void GuiButton::onMouseHoverStart()
{
	backgroundShape.setFillColor(sf::Color(200,200,200,255));
}

void GuiButton::onMouseHoverEnd()
{
	backgroundShape.setFillColor(sf::Color::White);
}

void GuiButton::onMouseLeftStart(ScreenPixelCoor mousePosition)
{
	clickFunc();
}


void GuiButton::setClickFunc(std::function<void()> func)
{
	clickFunc = func;
}

//bool GuiButton::click(sf::Vector2f point)
//{
//	return false;
//}
