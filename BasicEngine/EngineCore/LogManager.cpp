#include "LogManager.h"

namespace Core {
	//LogManager* LogManager::m_instance = nullptr;
	//Loglevel LogManager::currentLevel = Loglevel::TOTAL;

	LogManager::LogManager() : currentLevel(Loglevel::TOTAL)
	{
	}

	LogManager::~LogManager()
	{
	}

	void LogManager::SetLevel(Loglevel l)
	{
		LogManager::GetInstance().currentLevel = l;
	}

	Loglevel LogManager::GetLevel()
	{
		return LogManager::GetInstance().currentLevel;
	}

	void LogManager::Log(Loglevel l, const char * message)
	{
		//If within log level, print message
		if (l <= LogManager::GetInstance().currentLevel) {
			printf("%s\n",message);
		}
	}
}