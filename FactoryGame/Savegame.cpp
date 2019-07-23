#include "Savegame.h"
#include <fstream>
#include <ctime>
#include <string>
#include "GlobalDefines.h"

using namespace nlohmann;

/*
Savegame::Savegame(bool newGame, const std::string & saveName)
{
	
	if(newGame)
	{
		fileName = saveName;
		this->setSaveName(saveName);

		//for (char & c : fileName)
		//{
		//	if (!((c >= 65 && c <= 90) || (c >= 97 && c <= 122)))
		//	{
		//		c = '_';
		//	}
		//}

		saveToFile();
	}
	else
	{
		try {
			
		}
		catch (...) {

				assert("Error While loading savegame" && 0);
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
}

Savegame::~Savegame()
{
}

std::string Savegame::getSaveName()
{
	return j["name"];
}

void Savegame::setSaveName(std::string name)
{
	j["name"] = name;
}



bool Savegame::saveToFile()
{
	try {

		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo,&rawtime);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
		std::string str(buffer);

		std::ofstream ofs("saves/"+fileName+"-"+str+".json");
		ofs << j;
	}
	catch (...)
	{
		assert("Error while writing options to file" && 0);
	}
	return true;
}*/


Savegame::Savegame(const std::filesystem::path & folderName)
{
	folderPath = folderName;
	try {
		std::ifstream i(folderPath / "meta.json");
		i >> meta;
	}
	catch (...) {
		assert("Error while loading savegame" && 0);
	}
}

Savegame::~Savegame()
{
}

Savegame * Savegame::newGame(const std::string & name)
{
	assert(checkNewGameName(name)); //SaveGame already exists

	std::filesystem::path saveTo = userDataPath / "saves" / generateFolderName(name);
	//if (!std::filesystem::exists(saveTo))
	std::filesystem::create_directories(saveTo);
	std::filesystem::copy("recources/default_save",userDataPath/"saves"/generateFolderName(name),std::filesystem::copy_options::recursive);
	
	auto * retVal = new Savegame(userDataPath / "saves" / generateFolderName(name));
	retVal->setSaveName(name);
	retVal->setFileVersion(1);
	{
		time_t rawtime;
		struct tm timeinfo;
		char buffer[80];

		time(&rawtime);
		localtime_s(&timeinfo, &rawtime);

		strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", &timeinfo);
		std::string str(buffer);
		retVal->setCreatedTime(str);
		retVal->setModifiedTime(str);
	}
	retVal->saveToFile();
	return retVal;
}

bool Savegame::checkNewGameName(const std::string & name)
{
	return !std::filesystem::exists(userDataPath / "saves" / generateFolderName(name));
}

nlohmann::json Savegame::getAllSavegames()
{
	json retVal;
	int count = 0;
	for (auto& p : std::filesystem::directory_iterator(userDataPath / "saves"))
	{
		try {
			json jsPart;
			std::ifstream i(p.path()/"meta.json");
			i >> jsPart;
			if (jsPart["version"] == 1) 
			{
				retVal[count]["meta"] =  jsPart;
				retVal[count]["path"] = p.path().string();
				count++;
			}
		}
		catch (...) {}
	}

	return retVal;
}

int Savegame::getFileVersion()
{
	return meta["version"];
}

void Savegame::setFileVersion(int version)
{
	meta["version"] = version;
}

std::string Savegame::getSaveName()
{
	return meta["name"];
}

void Savegame::setSaveName(std::string name)
{
	meta["name"] = name;
}

std::string Savegame::getCreatedTime()
{
	return meta["createtime"];
}

void Savegame::setCreatedTime(std::string time)
{
	meta["createtime"] = time;
}

std::string Savegame::getModifiedTime()
{
	return meta["moditime"];
}

void Savegame::setModifiedTime(std::string time)
{
	meta["moditime"] = time;
}


std::string Savegame::generateFolderName(std::string name)
{
	std::string retVal("");
	
	for (int i = 0; i < name.size(); i++)
	{
		if ((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122)|| (name[i] >= 48 && name[i] <= 57))
		{
			retVal += name[i];
		}
	}

	return retVal;
}

bool Savegame::saveToFile()
{
	try {
		std::ofstream ofs(folderPath/"meta.json");
		ofs << meta;
	}
	catch (...)
	{
		assert("Error while writing options to file" && 0);
	}
	return true;
}