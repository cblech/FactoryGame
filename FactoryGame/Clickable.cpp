#include "Clickable.h"



Clickable::Clickable()
{
}


Clickable::~Clickable()
{
}
//
//void Clickable::mousePressed(sf::Event::MouseButtonEvent mouseEvent)
//{
//}
//
//void Clickable::mouseReleased(sf::Event::MouseButtonEvent mouseEvent)
//{
//}

bool Clickable::isBlocking()
{
	return blocking;
}

void Clickable::setHovering(bool h)
{
	hovering = h;
}

bool Clickable::getHovering()
{
	return hovering;
}


#pragma region MouseEvents

void Clickable::onMouseHoverStart(ScreenPixelCoor mousePosition)
{
}

void Clickable::onmouseHoverEnd(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseLeftStart(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseLeftEnd(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseRightStart(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseRightEnd(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseMiddleStart(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseMiddleEnd(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseFourStart(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseFourEnd(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseFiveStart(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseFiveEnd(ScreenPixelCoor mousePosition)
{
}

void Clickable::onMouseRawStart(ScreenPixelCoor mousePosition, sf::Mouse::Button button)
{
}

void Clickable::onMouseRawEnd(ScreenPixelCoor mousePosition, sf::Mouse::Button button)
{
}

#pragma endregion