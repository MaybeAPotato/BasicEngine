#ifndef PLAYER_H
#define PLAYER_H

namespace Core {
	class Player
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
