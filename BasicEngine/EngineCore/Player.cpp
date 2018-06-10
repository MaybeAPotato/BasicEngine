#include "Player.h"

#include <SDL/SDL.h>

#include "Camera.h"
#include "Input.h"

namespace Core {

	Player::Player() : playerCamera(new Camera()),playerInput(new Input())
	{
	}


	Player::~Player()
	{
		delete playerInput;
		playerInput = nullptr;

		delete playerCamera;
		playerCamera = nullptr;
	}
	bool Player::Init()
	{
		return true;
	}
	void Player::Update()
	{
		//Forward
		if (playerInput->IsKeyDown(SDLK_w)) {
			playerCamera->Keyboard(CameraMovement::FORWARD, 0.16f);
		}
		//Backward
		if ((playerInput->IsKeyDown(SDLK_s))) {
			playerCamera->Keyboard(CameraMovement::BACKWARD, 0.16f);
		}
		//Right
		if ((playerInput->IsKeyDown(SDLK_d))) {
			playerCamera->Keyboard(CameraMovement::RIGHT, 0.16f);
		}
		//Left
		if ((playerInput->IsKeyDown(SDLK_a))) {
			playerCamera->Keyboard(CameraMovement::LEFT, 0.16f);
		}
	}
	void Player::Render()
	{
	}
	bool Player::Shutdown()
	{
		if (!playerInput->Shutdown()) {
			return false;
		}

		return true;
	}
}