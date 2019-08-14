#pragma once
#include <vector>
#include <map>
#include "Clickable.h"
#include "Coords.h"

class ClickStack
{
public:
	ClickStack();
	~ClickStack();

	void registerClickable(Clickable * clickable, int level);
	void checkoutClickable(Clickable * clickable, int level = -1);

	void mousePressed(sf::Event::MouseButtonEvent mouseEvent);
	void mouseReleased(sf::Event::MouseButtonEvent mouseEvent);

	void mouseTick(ScreenPixelCoor mousePosition);


private:
	 std::vector<Clickable *> clickables[100];
};

