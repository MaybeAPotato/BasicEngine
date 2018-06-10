#ifndef ENGINE_H
#define ENGINE_H

struct SDL_Window;
struct SDL_Surface;

namespace Core {
	class Engine
	{
		//Is the engine running
		bool isRunning;
		class Window* engineWindow;
		class Graphic* engineGraphic;
		class Clock* engineClock;
		class SystemUI* engineUI;
		class Input* engineInput;

		class AssetManager* engineAssetManager;

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