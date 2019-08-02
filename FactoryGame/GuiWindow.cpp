#include "GuiWindow.h"



GuiWindow::GuiWindow()
{
	background.setFillColor(sf::Color(180,180,255,255));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(1.f);
}


GuiWindow::~GuiWindow()
{
}

void GuiWindow::setSize(sf::Vector2f size)
{
	background.setSize(size);
}

sf::Vector2f GuiWindow::getSize()
{
	return background.getSize();
}

void GuiWindow::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getTransform();
	target.draw(background, states);
}
