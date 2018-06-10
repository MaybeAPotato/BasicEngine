#include "Input.h"
#include <SDL/SDL.h>
#include <stdio.h>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"

namespace Core {
	Input::Input() : System(SystemType::INPUT), requestedQuit(false)
	{
	}

	Input::~Input()
	{
	}

	bool Input::Init() {
		return true;
	}
	void Input::Update() {
		oldkeys = keys;

		SDL_Event e;

		while (SDL_PollEvent(&e) != 0) {
			//Check for event type
			switch (e.type) {
			//Send to UI
			ImGui_ImplSdlGL3_ProcessEvent(&e);
			//Is key down
			case(SDL_KEYDOWN):
				//Check for key
				keys[e.key.keysym.sym] = true;
				break;
			//For mouse movement
			//case(SDL_MOUSEMOTION):
			//	break;
			case(SDL_KEYUP):
				keys[e.key.keysym.sym] = false;
				break;
			//Is quit
			case(SDL_QUIT):
				requestedQuit = true;
				break;
			}
		}
	}
	void Input::Render(){
	}
	bool Input::Shutdown() {
		return true;
	}
	SystemType Input::getSystemType() {
		return SystemType::INPUT;
	}
	DirectionInput Input::getDirectionInput() {
		return dr;
	}
	bool Input::IsKeyDown(unsigned int key)
	{
		auto it = keys.find(key);

		if (it != keys.end()) {
			//Returns true or false based on the state of the map
			return keys[key];
		}

		//The key has never been pressed
		return false;
	}
	bool Input::IsKeyUp(unsigned int key)
	{
		auto it = keys.find(key);

		if (it != keys.end()) {
			return !keys[key];
		}

		//Key has never been pressed
		return true;
	}
	bool Input::WasKeyPressed(unsigned int key)
	{
		auto it = oldkeys.find(key);

		//If key was in old array
		if (it != oldkeys.end()) {
				 //If false and if true
			return !oldkeys[key] && keys[key];
		}

		return keys[key];
	}
	bool Input::WasKeyReleased(unsigned int key)
	{
		auto it = oldkeys.find(key);

		//If key was in old array
		if (it != oldkeys.end()) {
				 //If true and if false
			return oldkeys[key] && !keys[key];
		}

		return false;
	}
}
