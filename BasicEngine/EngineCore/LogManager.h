#ifndef LOG_MANAGER_H
#define LOG_MANAGER_H

#include <iostream>

namespace Core {
	enum class Loglevel : unsigned __int8 {
		DEFAULT,
		ERROR,
		WARNING,
		TOTAL
	};

	class LogManager
	{
		LogManager();
		~LogManager();

		static LogManager* m_instance;
		static Loglevel currentLevel;

	public:
		static void SetLevel(Loglevel l);
		static void Log(Loglevel l, const char* message);
		static LogManager& GetInstance();
	};
}
#endif // !LOG_MANAGER_H