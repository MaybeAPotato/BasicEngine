#include "LogManager.h"


namespace Core {
	LogManager* LogManager::m_instance = nullptr;
	Loglevel LogManager::currentLevel = Loglevel::TOTAL;

	LogManager::LogManager()
	{
	}


	LogManager::~LogManager()
	{
	}

	void LogManager::SetLevel(Loglevel l)
	{
		currentLevel = l;
	}

	void LogManager::Log(Loglevel l, const char * message)
	{
		//If within log level, print message
		if (l < currentLevel) {
			printf("%s\n",message);
		}
	}

	LogManager& LogManager::GetInstance()
	{
		if (m_instance) {
			return *m_instance;
		}
		m_instance = new LogManager();
		return *m_instance;
	}
}