#pragma once
#include <SFML/Graphics.hpp>
class GuiWindow : public sf::Drawable, public sf::Transformable
{
public:
	GuiWindow();
	~GuiWindow();

	void setSize(sf::Vector2f size);
	sf::Vector2f getSize();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
	sf::RectangleShape background;
};

