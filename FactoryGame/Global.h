#pragma once
#include <filesystem>
#include "Options.h"
#include "GameMap.h"
#include "GuiWindow.h"
#include <vector>

#define spaceSizePX 64

class Global
{
public:
	Global();
	~Global();

	std::filesystem::path userDataPath;
	Options options;
	GameMap * openedMap;
	std::vector<GuiWindow *> guiWindows;
};

extern Global global;
