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
		
		//Map is a dictionary that has a key and a value
		//Current key state
		std::map<unsigned int, bool> keys;
		//Old key state
		std::map<unsigned int, bool> oldkeys;
		int mouseMotionX;
		int mouseMotionY;

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
		//Check if the the was released this frame
		bool WasKeyReleased(unsigned int key);

		//Get mouse motion in X direction
		int GetMouseMotionX() { return mouseMotionX; }
		//Get mouse motion in Y direction
		int GetMouseMotionY() { return mouseMotionY; }
	};
}

#endif // !INPUT_H

