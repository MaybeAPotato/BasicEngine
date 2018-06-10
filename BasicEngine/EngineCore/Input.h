#ifndef INPUT_H
#define INPUT_H
#include "System.h"
#include <map>

namespace Core {
	enum class DirectionInput: unsigned __int8 {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
		TOTAL
	};

	class Input : public System
	{
		bool requestedQuit;
		DirectionInput dr;

		//Current key state
		std::map<unsigned int, bool> keys;
		//Old key state
		std::map<unsigned int, bool> oldkeys;

	public:
		Input();
		~Input();

		bool Init() override;
		void Update() override;
		void Render() override;
		bool Shutdown() override;
		SystemType getSystemType();
		bool QuitRequested() const { return requestedQuit; }
		DirectionInput getDirectionInput();
		//Check if key is down (Key down)
		bool IsKeyDown(unsigned int key);
		//Check if key is not down
		bool IsKeyUp(unsigned int key);
		//Check if the key was pressed this frame (Key pressed)
		bool WasKeyPressed(unsigned int key);
		//Checl if the the was released this frame
		bool WasKeyReleased(unsigned int key);
	};
}

#endif // !INPUT_H

