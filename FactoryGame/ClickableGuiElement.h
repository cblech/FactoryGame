#pragma once
#include "Clickable.h"
#include "GuiElement.h"


class ClickableGuiElement :public Clickable
{
public:
	ClickableGuiElement();
	~ClickableGuiElement();

	bool doesHover(ScreenPixelCoor mousePosition) override;

};

