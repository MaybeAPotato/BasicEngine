#include <LogManager.h>

int main(int argc, char* argv[]) {
	Core::LogManager::Log(Core::Loglevel::DEFAULT, "Test message");

	getchar();
	return 0;
}