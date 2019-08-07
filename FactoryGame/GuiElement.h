#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

class GuiElement:public sf::Drawable
{
public:
	GuiElement();
	~GuiElement();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	virtual bool click(sf::Vector2f point) = 0;
	sf::Vector2f size;

protected:
	bool containsLocal(sf::Vector2f point);

};

typedef std::shared_ptr<GuiElement> GuiElementPtr;
