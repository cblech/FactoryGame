#include "GuiWindow.h"



GuiWindow::GuiWindow()
{
	background.setFillColor(sf::Color(180,180,255,255));
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(1.f);
	background.setSize({ 10.f, 10.f });
}


GuiWindow::~GuiWindow()
{
}

sf::Vector2f GuiWindow::getSize()
{
	return background.getSize();
}

void GuiWindow::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	states.transform = getTransform();
	target.draw(background, states);
	
	states.transform.translate(5.f,5.f);
	GuiContainer::draw(target, states);
}

void GuiWindow::solveSize()
{
	GuiContainer::solveSize();
	background.setSize(size + sf::Vector2f{ 10.f, 10.f });
}

