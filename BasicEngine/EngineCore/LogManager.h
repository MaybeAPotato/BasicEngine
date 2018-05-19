#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <iostream>
#include "Singleton.h"

namespace Core {
	enum class Loglevel : unsigned __int8 {
		DEFAULT,
		ERROR,
		WARNING,
		FATAL,
		TOTAL
	};

	class LogManager : public Singleton<LogManager>
	{
		friend Singleton;

		LogManager();

		Loglevel currentLevel;

	public:
		~LogManager();
		static void SetLevel(Loglevel l);
		static Loglevel GetLevel();
		static void Log(Loglevel l, const char* message);
	};
}
#endif // !LOG_MANAGER_H