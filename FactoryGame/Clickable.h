#pragma once
#include "Coords.h"
#include <SFML/Graphics.hpp>

class Clickable
{
public:
	Clickable();
	~Clickable();


	virtual bool doesHover(ScreenPixelCoor mousePosition)=0;

	/*void mousePressed(sf::Event::MouseButtonEvent mouseEvent);
	void mouseReleased(sf::Event::MouseButtonEvent mouseEvent);*/

	bool isBlocking();

#pragma region MouseEvents

	virtual void onMouseHoverStart();
	virtual void onMouseHoverEnd();
	
	virtual void onMouseTick(ScreenPixelCoor mousePosition);

	virtual void onMouseLeftStart(ScreenPixelCoor mousePosition);
	virtual void onMouseLeftEnd(ScreenPixelCoor mousePosition);
	
	virtual void onMouseRightStart(ScreenPixelCoor mousePosition);
	virtual void onMouseRightEnd(ScreenPixelCoor mousePosition);
	
	virtual void onMouseMiddleStart(ScreenPixelCoor mousePosition);
	virtual void onMouseMiddleEnd(ScreenPixelCoor mousePosition);
	
	virtual void onMouseFourStart(ScreenPixelCoor mousePosition);
	virtual void onMouseFourEnd(ScreenPixelCoor mousePosition);
	
	virtual void onMouseFiveStart(ScreenPixelCoor mousePosition);
	virtual void onMouseFiveEnd(ScreenPixelCoor mousePosition);
	
	virtual void onMouseRawStart(ScreenPixelCoor mousePosition, sf::Mouse::Button button);
	virtual void onMouseRawEnd(ScreenPixelCoor mousePosition, sf::Mouse::Button button);

#pragma endregion 

	void processMousePressed(sf::Event::MouseButtonEvent evnt);
	void processMouseReleased(sf::Event::MouseButtonEvent evnt);

	void setHovering(bool h);
	bool getHovering();

	void setEnabled(bool e);
	void enable();
	void disable();
	bool isEnabled();

	int getLevel();

protected:
	void setBlocking(bool b);

private:
	bool hovering = false;
	bool blocking = false;
	bool enabled = true;
	int level = 0;
};

