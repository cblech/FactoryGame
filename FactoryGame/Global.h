#pragma once
#include <filesystem>
#include "Options.h"
#include "GameMap.h"

#define spaceSizePX 64

class Global
{
public:
	Global();
	~Global();

	std::filesystem::path userDataPath;
	Options options;
	GameMap * openedMap;
	
};

extern Global global;
