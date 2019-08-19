#pragma once
#include "Clickable.h"
#include "GuiElement.h"



class ClickableGuiElement :public Clickable, public GuiElement
{
public:
	ClickableGuiElement(sf::FloatRect bounds);
	ClickableGuiElement();
	~ClickableGuiElement();

	bool doesHover(ScreenPixelCoor mousePosition) override;

	void setBounds(sf::FloatRect b);
	sf::FloatRect getBounds();

private:
	sf::FloatRect bounds;

};

