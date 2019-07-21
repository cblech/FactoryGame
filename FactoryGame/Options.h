#pragma once
#include "json.hpp"
#include "SFML/System.hpp"

class Options
{
public:
	Options();
	~Options();

	//resolution
	struct Resolution { bool isFullscreen; sf::Vector2i resolution; };
	Resolution getResolution();
	void setResolution(Resolution res);

	//v-sync
	bool getVSync();
	void setVSync(bool vs);

private:
	int fileVersion=0;
	nlohmann::json j;

	bool saveToFile();
};

