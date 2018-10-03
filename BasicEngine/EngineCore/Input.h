#ifndef INPUT_H
#define INPUT_H

#include "System.h"
#include <SDL/SDL_joystick.h>
#include <map>

namespace Core {
	enum class DirectionInput : unsigned __int8 {
		UP,
		DOWN,
		LEFT,
		RIGHT,
		NONE,
		TOTAL
	};

	class Input : public System
	{
		const int JOYSTICK_DEAD_ZONE = 8000;

		SDL_Joystick* joy;
		bool requestedQuit;
		DirectionInput dr;


		//Map is a dictionary that has a key and a value
		//Current key state
		std::map<unsigned int, bool> keys;
		//Old key state
		std::map<unsigned int, bool> oldkeys;
		//Mouse motion
		int mouseMotionX;
		int mouseMotionY;
		//Mouse wheel 
		int mouseWheelY;
		//Mouse button press
		int mouseButtonLeftPress;
		int mouseButtonRightPress;
		int mouseButtonMiddlePress;
		//Joystick left axis
		int joystickLeftAxisX;
		int joystickLeftAxisY;
		//Joystick right axis
		int joystickRightAxisX;
		int joystickRightAxisY;

		//Joystick axis
		int leftXAxis;
		int leftYAxis;
		int rightXAxis;
		int rightYAxis;

	public:
		Input();
		~Input();

		bool Init();
		void Update();
		void Render();
		bool Shutdown();
		//SystemType getSystemType();
		bool QuitRequested() { return requestedQuit; }
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
		inline int GetMouseMotionX() { return mouseMotionX; }
		//Get mouse motion in Y direction
		inline int GetMouseMotionY() { return mouseMotionY; }
		//Get mouse wheel y
		inline int GetMouseWheelY() { return mouseWheelY; }

		//Get joystick axis in X direction
		inline int GetJoyStickLeftAxisX() { return joystickLeftAxisX; }
		//Get joystick axis in Y direction
		inline int GetJoyStickLeftAxisY() { return joystickLeftAxisY; }
		//Get joystick axis in X direction
		inline int GetJoyStickRightAxisX() { return joystickRightAxisX; }
		//Get joystick axis in Y direction
		inline int GetJoyStickRightAxisY() { return joystickRightAxisY; }
	};
}
#endif // !INPUT_H

