#pragma once
#include <vector>
#include <list>
#include "Clickable.h"
#include "Coords.h"



class ClickStack
{
public:
	
	struct ClickableLevel
	{
		ClickableLevel(int l) :level(l) {}
		int level;
		std::vector<Clickable *> cbs;
	};

	
	ClickStack();
	~ClickStack();

	void registerClickable(Clickable * clickable, int level);
	void checkoutClickable(Clickable * clickable, int level = -1);

	void mousePressed(sf::Event::MouseButtonEvent mouseEvent);
	void mouseReleased(sf::Event::MouseButtonEvent mouseEvent);

	void mouseTick(ScreenPixelCoor mousePosition);


private:
	 std::list<ClickableLevel> clickables;
	 std::vector<Clickable *> currentyClicked;
};

bool operator< (const ClickStack::ClickableLevel & left, const ClickStack::ClickableLevel & right);

