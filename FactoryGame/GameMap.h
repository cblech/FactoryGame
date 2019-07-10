#pragma once
#include <SFML\Graphics.hpp>
#include <vector>

class GameMap : public sf::Drawable
{
public:
	enum Type
	{
		garage
	};

	GameMap(int id);
	~GameMap();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	bool initByFile(std::string filename);
private:
	enum SpaceType
	{
		none = 0,
		wall = 1,
		object = 2
	};

	struct Space
	{
		Space(int x, int y, int type)
		{
			coord.x = x;
			coord.y = y;
			spaceType = SpaceType(type);
		}
		sf::Vector2i coord; //The coordinates of this space
		SpaceType spaceType; //The type of this space (eg: none/air , wall , ...)

		Space * above = nullptr; //The neighbor above this space
		Space * below = nullptr; //The neighbor below this space
		Space * left = nullptr; //The neighbor left to this space
		Space * right = nullptr; //The neighbor right to this space
	};




	int id;
	Type type;
	sf::Vector2i size;

	std::vector<Space *> spaces;
	inline Space * getSpaceByCoord(int x, int y);

	sf::Texture backgroundTextrue;
	sf::Sprite backgroundSprite;

};

