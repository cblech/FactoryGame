#include "GuiWindow.h"

GuiWindow::GuiWindow(bool showBackground) :showBackground(showBackground)
{
	background.setFillColor(BACKGROUND_COLOR);
	background.setOutlineColor(sf::Color::Black);
	background.setOutlineThickness(1.f);
	background.setSize({ 10.f, 10.f });
	background.setOrigin(5.f, 5.f);

	setBounds({ 0,0,0,0 });

	setBlocking(showBackground);
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
	states.transform = totalTransform;
	if (showBackground)
	{
		target.draw(background, states);
		//states.transform.translate(5.f, 5.f);
	}

	container.draw(target, states);
}

void GuiWindow::solveSize()
{
	if(showBackground) totalTransform.translate(5.f, 5.f);
	container.totalTransform = totalTransform;
	container.solveSize();

	if (showBackground)
	{
		size = container.size + sf::Vector2f{10.f, 10.f};
		background.setSize(size);
		setBounds({ -5.f,-5.f,size.x,size.y });
	}
	else
	{
		size = container.size;
		setBounds({0,0,size.x,size.y});
	}
	
}

bool GuiWindow::contains(sf::Vector2f point)
{
	auto tpoint = totalTransform.getInverse()*point;
	return background.getGlobalBounds().contains(tpoint);
}



//bool GuiWindow::click(sf::Vector2f point)
//{
//	if (!contains(point))
//		return false;
//
//	sf::Transform tr = getTransform();
//	if(showBackground) tr.translate(5.0f, 5.0f);
//	auto tpoint = tr.getInverse()*point;
//
//	if (showBackground)
//	{
//		GuiContainer::click(tpoint);
//	}
//	else
//	{
//		return GuiContainer::click(tpoint);
//	}
//
//	return true;
//}

