#include "GuiWindow.h"



GuiWindow::GuiWindow(bool showBackground) :showBackground(showBackground)
{
	background.setFillColor(sf::Color(180, 180, 255, 255));
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
	if (showBackground)
	{
		target.draw(background, states);
		states.transform.translate(5.f, 5.f);
	}
	GuiContainer::draw(target, states);
}

void GuiWindow::solveSize()
{
	GuiContainer::solveSize();
	background.setSize(size + sf::Vector2f{ 10.f, 10.f });
}

bool GuiWindow::contains(sf::Vector2f point)
{
	auto tpoint = getInverseTransform()*point;
	return background.getGlobalBounds().contains(tpoint);
}

bool GuiWindow::click(sf::Vector2f point)
{
	if (!contains(point))
		return false;

	sf::Transform tr = getTransform();
	if(showBackground) tr.translate(5.0f, 5.0f);
	auto tpoint = tr.getInverse()*point;

	if (showBackground)
	{
		GuiContainer::click(tpoint);
	}
	else
	{
		return GuiContainer::click(tpoint);
	}

	return true;
}

