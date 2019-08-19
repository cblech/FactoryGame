#include "ClickableGuiElement.h"
#include "Global.h"

ClickableGuiElement::ClickableGuiElement(sf::FloatRect bounds) :bounds(bounds)
{
	setBlocking(true);

	global.clickStack.registerClickable(this,83);
}

ClickableGuiElement::ClickableGuiElement() : ClickableGuiElement({0,0,0,0})
{
}

ClickableGuiElement::~ClickableGuiElement()
{
	global.clickStack.checkoutClickable(this, 83);
}

bool ClickableGuiElement::doesHover(ScreenPixelCoor mousePosition)
{
	mousePosition = ScreenPixelCoor(totalTransform.getInverse().transformPoint(sf::Vector2f(mousePosition)));
	return (mousePosition.x > bounds.left)
		&& (mousePosition.x < bounds.left + bounds.width)
		&& (mousePosition.y > bounds.top)
		&& (mousePosition.y < bounds.top + bounds.height);
}

void ClickableGuiElement::setBounds(sf::FloatRect b)
{
	bounds = b;
}

sf::FloatRect ClickableGuiElement::getBounds()
{
	return bounds;
}
