#include "Engine.h"
#include "LogManager.h"

#include <SDL/SDL.h>
#include <chrono>
#include <Windows.h>

#include "Window.h"
#include "SystemManager.h"

namespace Core {
	Engine::Engine() : isRunning(true),engineWindow(new Window()){
		SystemManager::GetInstance().AddSystem(*engineWindow);
	}

	Engine::~Engine(){
	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine shutdown");
	#endif
	#if _DEBUG
		LogManager::Log(Core::Loglevel::WARNING, "Closing SDL");
	#endif
		CloseSDL();

	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Shutdown");
	#endif
		Shutdown();
	}
	
	int Engine::Init(){
		//Get instance of log manager
		LogManager::GetInstance();
		//Used to check init success
		bool success = 0;
	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine init");
	#endif
		if (!InitSDL()) {
			LogManager::Log(Core::Loglevel::ERROR, "Could not init SDL");
			success = 1;
		}
		return success;
	}

	bool Engine::InitSDL(){
		bool success = true;
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
			LogManager::Log(Core::Loglevel::ERROR, "Failed to init SDL");
			success = false;
		}
		else {
			if (!SystemManager::GetInstance().Init()) {
				LogManager::Log(Core::Loglevel::ERROR, "Error in init system");
			}
		}

		return success;
	}

	bool Engine::CloseSDL()
	{
		bool success = true;

		return success;
	}

	void Engine::Run()
	{
	#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine run");
	#endif
		while (isRunning) {

			Update();
			Render();

			
		}
	}

	void Engine::Update(){
		//Event handling
		const auto start = std::chrono::high_resolution_clock().now();

		//Getting all event that happened
		SDL_Event e;

		LARGE_INTEGER t;
		QueryPerformanceFrequency(&t);

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

		const auto end = std::chrono::high_resolution_clock().now();
		const auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		std::cout << durationMS.count() << " ms" << std::endl;
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
		LogManager::Log(Core::Loglevel::DEFAULT, "Window shutdown");
	#endif

		//If the window failed to shutdown
		if (!SystemManager::GetInstance().Shutdown()) {
		#if _DEBUG
			LogManager::Log(Core::Loglevel::ERROR, "Failed to properly shutdown the window");
		#endif
			success = 1;
		}



		return success;
	}
}
