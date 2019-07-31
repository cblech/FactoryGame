#include "Savegame.h"
#include <fstream>
#include <ctime>
#include <string>
#include "GlobalDefines.h"
#include "Coords.h"


using namespace nlohmann;

Savegame::Savegame(const std::filesystem::path & folderName)
{
	folderPath = folderName;
	try {
		std::ifstream im(folderPath / "meta.json");
		im >> jmeta;
		std::ifstream io(folderPath / "objects.json");
		io >> jobjects;
	}
	catch (...) {
		assert("Error while loading savegame" && 0);
	}
}

Savegame::~Savegame()
{
}

void Savegame::gatherAndSave(std::vector<GameMap*> loadedMaps)
{	
	for (auto * m : loadedMaps)
	{
		nlohmann::json tj = nlohmann::json::array();
			
		for (auto o : m->getObjects()) 
		{
			tj.push_back(*o);
		}

		switch (m->getID())
		{
		case 1:
			jobjects["garage"] = tj;
			break;
		case 2:
			jobjects["shipyard"] = tj;
			break;
		
		default:
			assert("unknown map" && 0);
			break;
		}
	}

	saveToFile();
}

bool Savegame::saveToFile()
{
	const bool fancyjson = true;//makes the json in the file more human readable

	//save jsons to file
	try {
		std::ofstream ofsm(folderPath / "meta.json");
		ofsm << (fancyjson ? std::setw(4) : std::setw(0)) << jmeta;

		std::ofstream ofso(folderPath / "objects.json");
		ofso << (fancyjson ? std::setw(4) : std::setw(0)) << jobjects;
	}
	catch (...)
	{
		assert("Error while writing options to file" && 0);
	}
	return true;
}

Savegame * Savegame::newGame(const std::string & name)
{
	assert(checkNewGameName(name)); //SaveGame already exists

	std::filesystem::path saveTo = userDataPath / "saves" / generateFolderName(name);
	//if (!std::filesystem::exists(saveTo))
	std::filesystem::create_directories(saveTo);
	std::filesystem::copy("recources/default_save", userDataPath / "saves" / generateFolderName(name), std::filesystem::copy_options::recursive);

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

//void to_json(nlohmann::json& j, const MapSpaceCoor& p) {
//	j = nlohmann::json{ p.x, p.y };
//}
//
//void from_json(const nlohmann::json& j, MapSpaceCoor& p) {
//	j.at(0).get_to(p.x);
//	j.at(1).get_to(p.y);
//}


json Savegame::getAllSavegames()
{
	MapSpaceCoor testCo{ 4,8 };
	json test = testCo;

	json retVal;
	int count = 0;
	for (auto& p : std::filesystem::directory_iterator(userDataPath / "saves"))
	{
		try {
			json jsPart;
			std::ifstream i(p.path() / "meta.json");
			i >> jsPart;
			if (jsPart["version"] == 1)
			{
				retVal[count]["meta"] = jsPart;
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
	return jmeta["version"];
}

void Savegame::setFileVersion(int version)
{
	jmeta["version"] = version;
}

std::string Savegame::getSaveName()
{
	return jmeta["name"];
}

void Savegame::setSaveName(std::string name)
{
	jmeta["name"] = name;
}

std::string Savegame::getCreatedTime()
{
	return jmeta["createtime"];
}

void Savegame::setCreatedTime(std::string time)
{
	jmeta["createtime"] = time;
}

std::string Savegame::getModifiedTime()
{
	return jmeta["moditime"];
}

void Savegame::setModifiedTime(std::string time)
{
	jmeta["moditime"] = time;
}

nlohmann::json Savegame::getObjects()
{
	return jobjects;
}




std::string Savegame::generateFolderName(std::string name)
{
	std::string retVal("");

	for (int i = 0; i < name.size(); i++)
	{
		if ((name[i] >= 65 && name[i] <= 90) || (name[i] >= 97 && name[i] <= 122) || (name[i] >= 48 && name[i] <= 57))
		{
			retVal += name[i];
		}
	}

	return retVal;
}
