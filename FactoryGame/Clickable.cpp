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

void Clickable::processMousePressed(sf::Event::MouseButtonEvent evnt)
{
	onMouseRawStart({ evnt.x ,evnt.y }, evnt.button);
	switch (evnt.button) 
	{
	case sf::Mouse::Button::Left:
		onMouseLeftStart({ evnt.x ,evnt.y });
		break;
	case sf::Mouse::Button::Right:
		onMouseRightStart({ evnt.x ,evnt.y });
		break;
	case sf::Mouse::Button::Middle:
		onMouseMiddleStart({ evnt.x ,evnt.y });
		break;
	case sf::Mouse::Button::XButton1:
		onMouseFourStart({ evnt.x ,evnt.y });
		break;
	case sf::Mouse::Button::XButton2:
		onMouseFiveStart({ evnt.x ,evnt.y });
		break;
	default:
		break;
	}
}

void Clickable::processMouseReleased(sf::Event::MouseButtonEvent evnt)
{
	onMouseRawEnd({ evnt.x ,evnt.y }, evnt.button);
	switch (evnt.button)
	{
	case sf::Mouse::Button::Left:
		onMouseLeftEnd({ evnt.x ,evnt.y });
		break;
	case sf::Mouse::Button::Right:
		onMouseRightEnd({ evnt.x ,evnt.y });
		break;
	case sf::Mouse::Button::Middle:
		onMouseMiddleEnd({ evnt.x ,evnt.y });
		break;
	case sf::Mouse::Button::XButton1:
		onMouseFourEnd({ evnt.x ,evnt.y });
		break;
	case sf::Mouse::Button::XButton2:
		onMouseFiveEnd({ evnt.x ,evnt.y });
		break;
	default:
		break;
	}
}

void Clickable::setHovering(bool h)
{

	if (h != hovering)
	{
		hovering = h;
		if (hovering)
			onMouseHoverStart();
		else
			onMouseHoverEnd();
	}
}

bool Clickable::getHovering()
{
	return hovering;
}

void Clickable::setEnabled(bool e)
{
	enabled = e;
}

void Clickable::enable()
{
	enabled = true;
}

void Clickable::disable()
{
	enabled = false;
}

bool Clickable::isEnabled()
{
	return enabled;
}

int Clickable::getLevel()
{
	return level;
}

void Clickable::setBlocking(bool b)
{
	blocking = b;
}


#pragma region MouseEvents

void Clickable::onMouseHoverStart()
{
}

void Clickable::onMouseHoverEnd()
{
}

void Clickable::onMouseTick(ScreenPixelCoor mousePosition)
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