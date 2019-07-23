#pragma once
#include "json.hpp"
#include <filesystem>

class Savegame
{
public:
	Savegame(const std::filesystem::path & folderName);
	~Savegame();

	static Savegame * newGame(const std::string & name);
	static bool checkNewGameName(const std::string & name);
	static nlohmann::json getAllSavegames();

	//fileVersion
	int getFileVersion();
	void setFileVersion(int version);
	
	//saveName
	std::string getSaveName();
	void setSaveName(std::string name);
	
	//created
	std::string getCreatedTime();
	void setCreatedTime(std::string time);
	
	//modified
	std::string getModifiedTime();
	void setModifiedTime(std::string time);


private:
	nlohmann::json meta;

	int fileVersion = 0;
	std::filesystem::path folderPath;

	static std::string generateFolderName(std::string name);
	bool saveToFile();
};

