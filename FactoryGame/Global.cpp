#include "Global.h"



Global::Global()
{
	{
		char *pValue;
		size_t len;
		_dupenv_s(&pValue, &len, "APPDATA");
		userDataPath = std::filesystem::path(pValue) / "FactoryGame";
	}
}


Global::~Global()
{
}
