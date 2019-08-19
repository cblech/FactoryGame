#pragma once
#include "ClickableGuiElement.h"
#include <functional>

class GuiButton : public ClickableGuiElement
{
public:
	GuiButton(sf::Vector2f size);
	~GuiButton();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void onMouseHoverStart() override;
	void onMouseHoverEnd() override;

	void onMouseLeftStart(ScreenPixelCoor mousePosition) override;

	void setClickFunc(std::function<void()> func);

	//virtual bool click(sf::Vector2f point);
private:
	std::function<void()> clickFunc;
	sf::RectangleShape backgroundShape;
};

