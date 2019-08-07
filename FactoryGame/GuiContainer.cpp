#include "GuiContainer.h"



GuiContainer::GuiContainer()
{
}


GuiContainer::~GuiContainer()
{
}

void GuiContainer::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	
	if (sortVertical)
	{
		for (auto e : elements) 
		{
			target.draw(*e, states);
			states.transform.translate(0.f, e->size.y);
		}
	}
	else
	{
		for (auto e : elements)
		{
			target.draw(*e, states);
			states.transform.translate(e->size.x,0.f);
		}
	}
}

void GuiContainer::addElement(GuiElementPtr element)
{
	elements.push_back(element);
	solveSize();
}

void GuiContainer::clearElements()
{
	elements.clear();
	size = sf::Vector2f{ 0.f,0.f };
}

void GuiContainer::setVertical()
{
	sortVertical = true;
	solveSize();
}

void GuiContainer::setHorizontal()
{
	sortVertical = false;
	solveSize();
}

void GuiContainer::solveSize()
{
	if (sortVertical)
	{
		float add=0;
		float max = 0;
		for (auto e : elements)
		{
			add += e->size.y;
			if (max < e->size.x)
				max = e->size.x;
		}
		size = { max,add };
	}
	else
	{
		float add = 0;
		float max = 0;
		for (auto e : elements)
		{
			add += e->size.x;
			if (max < e->size.y)
				max = e->size.y;
		}
		size = { add,max };
	}
}

bool GuiContainer::click(sf::Vector2f point)
{
	if (sortVertical)
	{
		for (auto e : elements)
		{
			if (point.y < e->size.y)
			{
				if (e->click(point))
					return true;
				else
					return false;
				break;
			}
			else {
				point.y -= e->size.y;
			}
		}
	}
	else
	{
		for (auto e : elements)
		{
			if (point.x < e->size.x)
			{
				if (e->click(point))
					return true;
				else
					return false;
				break;
			}
			else {
				point.x -= e->size.x;
			}
		}
	}
	return false;
}
