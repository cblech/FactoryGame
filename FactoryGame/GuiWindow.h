#pragma once
#include <SFML/Graphics.hpp>
#include "GuiContainer.h"
#include "ClickableGuiElement.h"

class GuiWindow : public ClickableGuiElement
{
public:
	GuiWindow(bool showBackground = true);
	~GuiWindow();

	sf::Vector2f getSize();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	virtual void solveSize();
	bool contains(sf::Vector2f point);
	//virtual bool click(sf::Vector2f point);

	//using ClickableGuiElement::totalTransform;
	//using GuiContainer::totalTransform;

	GuiContainer container;

private:
	sf::RectangleShape background;
	bool showBackground;
	//GuiContainer container;
};

