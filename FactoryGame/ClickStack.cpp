#include "ClickStack.h"



ClickStack::ClickStack()
{
}


ClickStack::~ClickStack()
{
}

/*
LEVELS:

90+ : Main Menu

80+ : Overlay



10+ : Map
*/

void ClickStack::registerClickable(Clickable * clickable, int level)
{
	clickables[level].push_back(clickable);
}

void ClickStack::checkoutClickable(Clickable * clickable, int level)
{
	if (level == -1)
	{
		for (auto c1 : clickables)
			for (auto * c2 : c1)
				if (c2 == clickable)
				{
					c1.erase(std::remove(clickables[level].begin(), clickables[level].end(), clickable));
					return;
				}
	}
	else
	{
		clickables[level].erase(std::remove(clickables[level].begin(), clickables[level].end(), clickable));
	}



}

void ClickStack::mousePressed(sf::Event::MouseButtonEvent mouseEvent)
{
}

void ClickStack::mouseReleased(sf::Event::MouseButtonEvent mouseEvent)
{
}

void ClickStack::mouseTick(ScreenPixelCoor mousePosition)
{
	bool brk = false;
	for (auto cv : clickables)
	{
		if (brk)
			for (auto c : cv)
				c->setHovering(false);
		else
			for (auto c : cv)
			{
				if (c->doesHover(mousePosition))
				{
					c->setHovering(true);
					if (c->isBlocking())
						brk = true;
				}
				else
				{
					c->setHovering(false);
				}

			}
	}
}
