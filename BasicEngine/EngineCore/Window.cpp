#include "Window.h"
#include <SDL/SDL.h>

namespace Core {

	Window::Window() : System(SystemType::WINDOW),windowName("Basic Engine"), windowWidth(800), windowHeight(600)
	{
	}

	Window::Window(char * name, unsigned int width, unsigned int height) : System(SystemType::WINDOW),windowName(name),windowWidth(width),windowHeight(height)
	{
	}

	Window::~Window()
	{
		Shutdown();
	}
	bool Window::Init()
	{
		bool success = true;

		window = SDL_CreateWindow(windowName, 100, 100, windowWidth, windowHeight, SDL_WINDOW_SHOWN);
		//If failed to create window
		if (!window) {
			success = false;
		}
		//if not set surface
		else {
			screenSurface = SDL_GetWindowSurface(window);
		}

		return success;
	}
	void Window::Update()
	{
		SDL_UpdateWindowSurface(window);
	}
	void Window::Render()
	{
	}
	bool Window::Shutdown()
	{
		bool success = true;

		SDL_FreeSurface(screenSurface);
		screenSurface = nullptr;

		SDL_DestroyWindow(window);
		window = nullptr;

		if (window || screenSurface) {
			success = false;
		}

		return success;
	}
}
