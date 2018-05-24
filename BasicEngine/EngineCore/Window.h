#ifndef  WINDOW_H
#define WINDOW_H

#include "System.h"

struct SDL_Window;
struct SDL_Surface;

namespace Core {
	class Window : public System
	{
		SDL_Window* window;
		SDL_Surface* screenSurface;

		const char* windowName;
		const unsigned int windowWidth;
		const unsigned int windowHeight;

	public:
		Window();
		Window(char* name, unsigned int width, unsigned int height);
		~Window();

		bool Init() override;
		void Update() override;
		void Render() override;
		bool Shutdown() override;

		SDL_Surface* GetScreenSurface() { return screenSurface; }
		SDL_Window* GetWindow() { return window; }

		bool InitSDL();
		bool CloseSDL();
	};
}

#endif