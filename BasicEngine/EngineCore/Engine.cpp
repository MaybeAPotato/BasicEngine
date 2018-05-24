#include "Engine.h"
#include "LogManager.h"

#include <SDL/SDL.h>
#include <Windows.h>
#include <GL/glew.h>

#include "Window.h"
#include "SystemManager.h"
#include "AssetManager.h"
#include "Graphic.h"
#include "Clock.h"

namespace Core {
	Engine::Engine() : isRunning(true),engineWindow(new Window()),engineGraphic(new Graphic()),engineClock(new Clock()){
		SystemManager::GetInstance().AddSystem(*engineWindow);
		SystemManager::GetInstance().AddSystem(*engineGraphic);
		SystemManager::GetInstance().AddSystem(*engineClock);
	}

	Engine::~Engine(){
	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine shutdown");
	#endif
		delete engineWindow;
		engineWindow = nullptr;

		delete engineGraphic;
		engineGraphic = nullptr;

	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Shutdown");
	#endif
	}
	
	int Engine::Init(){
		//auto start = std::chrono::high_resolution_clock().now();
		//Get instance of log manager
		LogManager::GetInstance();

		//Used to check init success
		int success = 0;
	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine init");
	#endif

		if (!SystemManager::GetInstance().Init()) {
			success = 1;
		}


		return success;

		//auto end = std::chrono::high_resolution_clock().now();
		//auto durationMS = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		//std::cout << "Engine init took " << durationMS.count() << " ms" << std::endl;
	}

	void Engine::Run()
	{
	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine run");
	#endif
		//Infinite engine loop
		while (isRunning) {
			Update();
			Render();
		}

		Shutdown();
	}

	void Engine::Update(){
		//Event handling
		//const auto start = std::chrono::high_resolution_clock().now();

		//Getting all event that happened
		SDL_Event e;

		//LARGE_INTEGER t;
		//QueryPerformanceFrequency(&t);

		while (SDL_PollEvent(&e) != 0) {
			switch (e.type)
			{
			//For closing the window
			case(SDL_QUIT):
				isRunning = false;
				break;
			default:
				break;
			}
		}

		SystemManager::GetInstance().Update();

		//const auto end = std::chrono::high_resolution_clock().now();
		//const auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		//std::cout << durationMS.count() << " ms" << std::endl;
	}

	void Engine::Render() {
		SystemManager::GetInstance().Render();
	}

	int Engine::Shutdown()
	{
	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine shutdown");
	#endif
		int success = 0;

	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Systems shutdown");
	#endif

		//If the window failed to shutdown
		if (!SystemManager::GetInstance().Shutdown()) {
		#if _DEBUG
			LogManager::Log(Core::Loglevel::FATAL, "Failed to properly shutdown a system");
		#endif
			success = 1;
		}



		return success;
	}
}
