#include <Engine.h>
#include <LogManager.h>

int main(int argc, char* argv[]) {
	Core::Engine e;

	if (e.Init() == 0) {
		e.Run();
	}

	//getchar();
	return 0;
}