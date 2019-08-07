#pragma once
#include <SFML/Graphics.hpp>
#include "GuiContainer.h"

class GuiWindow : public GuiContainer, public sf::Transformable
{
public:
	GuiWindow(bool showBackground = true);
	~GuiWindow();

	sf::Vector2f getSize();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	virtual void solveSize();
	bool contains(sf::Vector2f point);
	virtual bool click(sf::Vector2f point);

private:
	sf::RectangleShape background;
	bool showBackground;
	//GuiContainer container;
};

