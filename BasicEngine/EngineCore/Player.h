#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"

namespace Core {
	class Player : public GameObject
	{
		class Camera* playerCamera;
		class Input* playerInput;

	public:
		Player();
		~Player();

		bool Init();
		void Update();
		void Render();
		bool Shutdown();
	};
}
#endif // !PLAYER_H
