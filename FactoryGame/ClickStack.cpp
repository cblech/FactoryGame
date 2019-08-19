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
	for (auto & c : clickables)
	{
		if (c.level == level) 
		{
			c.cbs.push_back(clickable);
			return;
		}
	}
	auto cl = ClickStack::ClickableLevel(level);
	cl.cbs.push_back(clickable);
	clickables.push_back(cl);
	clickables.sort();
}

void ClickStack::checkoutClickable(Clickable * clickable, int level)
{
	for (auto c : clickables)
	{
		if (c.level == level)
		{
			c.cbs.push_back(clickable);
			return;
		}
	}
	/*if (level == -1)
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
	}*/

}

void ClickStack::mousePressed(sf::Event::MouseButtonEvent mouseEvent)
{
	bool brk = false;
	for (auto cv : clickables)
	{
		for (auto c : cv.cbs)
		{
			if (c->doesHover({ mouseEvent.x,mouseEvent.y }))
			{
				c->processMousePressed(mouseEvent);
				currentyClicked.push_back(c);
				if (c->isBlocking())
					brk = true;
			}
		}
		if (brk)
			break;
	}
}

void ClickStack::mouseReleased(sf::Event::MouseButtonEvent mouseEvent)
{
	for (auto e : currentyClicked)
	{
		e->processMouseReleased(mouseEvent);
	}
}

void ClickStack::mouseTick(ScreenPixelCoor mousePosition)
{
	bool brk = false;
	for (auto cv : clickables)
	{
		if (brk)
			for (auto c : cv.cbs)
			{
				c->setHovering(false);
				c->onMouseTick(mousePosition);
			}
		else
			for (auto c : cv.cbs)
			{
				if (c->isEnabled())
				{
					c->onMouseTick(mousePosition);

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
}

bool operator<(const ClickStack::ClickableLevel & left, const ClickStack::ClickableLevel & right)
{
	return left.level>right.level;
}
