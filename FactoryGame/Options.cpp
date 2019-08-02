#include "Options.h"
#include <fstream>
#include <assert.h>
#include <filesystem>

using namespace nlohmann;


Options::Options()
{
	try {
		//throw 0;
		std::ifstream i("options.json");
		i >> j;
	}
	catch (...) {
		try {
			std::ifstream di("recources/defalut_options.json");
			di >> j;
			saveToFile();
		}
		catch(...)
		{
			assert("Error While copying and interpreting default options" && 0);
		}
	}

	if (j["filetype"] == "factoryGameOptions0.1")
	{
		fileVersion = 1;
	} 
	else
	{
		assert("invalid options file version" && 0);
	}
}


Options::~Options()
{
}

Options::Resolution Options::getResolution()
{
	try {
		return Resolution{ j["resolution"][0].get<bool>(),sf::Vector2i(j["resolution"][1].get<int>(),j["resolution"][2].get<int>()) };
	}
	catch (...)
	{
		assert("Falty options" && 0);
	}
}

void Options::setResolution(Resolution res)
{
	j["resolution"] = {res.isFullscreen,res.resolution.x,res.resolution.y};
	saveToFile();
}

bool Options::getVSync()
{
	return j["vsync"];
}

void Options::setVSync(bool vs)
{
	j["vsync"] = vs;
	saveToFile();
}

bool Options::saveToFile()
{
	try {
		std::ofstream ofs("options.json");
		ofs << j;
	}
	catch (...)
	{
		assert("Error while writing options to file" && 0);
	}
	return true;
}
