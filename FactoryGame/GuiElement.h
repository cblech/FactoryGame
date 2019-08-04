#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GuiElement:public sf::Drawable
{
public:
	GuiElement();
	~GuiElement();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	sf::Vector2f size;

};

typedef std::shared_ptr<GuiElement> GuiElementPtr;
