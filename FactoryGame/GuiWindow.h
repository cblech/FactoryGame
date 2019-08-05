#pragma once
#include <SFML/Graphics.hpp>
#include "GuiContainer.h"

class GuiWindow : public GuiContainer, public sf::Transformable
{
public:
	GuiWindow();
	~GuiWindow();

	sf::Vector2f getSize();


	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;


	virtual void solveSize();

private:
	sf::RectangleShape background;
	GuiContainer container;
};

