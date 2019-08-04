#pragma once
#include "GuiElement.h"
#include <vector>

#define MakeGuiContainerPtr std::make_shared<GuiContainer>;

class GuiContainer: public GuiElement
{
public:
	GuiContainer();
	~GuiContainer();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void addElement(GuiElementPtr element);
	void clearElements();

	void setVertical();
	void setHorizontal();

protected:
	virtual void solveSize();

private:
	std::vector<GuiElementPtr> elements;
	bool sortVertical = true;
	};

