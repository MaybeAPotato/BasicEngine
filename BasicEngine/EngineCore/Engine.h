#ifndef ENGINE_H
#define ENGINE_H

class SDL_Window;
class SDL_Surface;

namespace Core {
	class Engine
	{
		//Is the engine running
		bool isRunning;
		class Window* engineWindow;
		class Graphic* engineGraphic;
		class Clock* engineClock;

	public:
		Engine();
		~Engine();

		int Init();
		void Run();
		int Shutdown();
		void Update();
		void Render();
	};
}

#endif // !ENGINE_H