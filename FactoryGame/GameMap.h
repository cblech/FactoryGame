#pragma once
#include <SFML\Graphics.hpp>

class GameMap: public sf::Drawable
{
public:
	GameMap(int id);
	~GameMap();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool initByFile(std::string filename);
private:
	int id;
	sf::Vector2i size;

	sf::Texture backgroundTextrue;
	sf::Sprite backgroundSprite;

};

