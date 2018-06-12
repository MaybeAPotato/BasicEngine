#include "Camera.h"

namespace Core {
	Camera::Camera() : Position(0.0f,0.0f,0.0f), Forward(0.0f,0.0f,-1.0f), Up(0.0f,1.0f,0.0f), Right(1.0f,0.0f,0.0f), WorldUp(0.0f,1.0f,0.0f), Yaw(YAW), Pitch(PITCH), MovementSpeed(1.0f), MouseSensitivity(MOUSE_SENSITIVITY), FOV(FIELD_OF_VIEW)
	{
	}

	Camera::Camera(glm::vec3 pos, glm::vec3 forward, glm::vec3 up, glm::vec3 right, glm::vec3 worldup, float yaw, float pitch, float movespeed, float sensitivity, float fov) : Position(pos),Forward(forward),Up(up),Right(right),WorldUp(worldup),Yaw(yaw),Pitch(pitch), MovementSpeed(movespeed),MouseSensitivity(sensitivity),FOV(fov)
	{
	}
	bool Camera::Init()
	{
		return true;
	}
	void Camera::Update()
	{
		glm::vec3 forward;

		forward.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
		forward.y = sin(glm::radians(Pitch));
		forward.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));

		Forward = glm::normalize(Forward);
		Right = glm::normalize(glm::cross(Forward, WorldUp));
		Up = glm::normalize(glm::cross(Right, Forward));
	}

	void Camera::Render()
	{
	}

	bool Camera::Shutdown()
	{
		return true;
	}

	void Camera::Keyboard(CameraMovement direction, float deltaTime)
	{
		float velocity = MovementSpeed * deltaTime;
		switch (direction)
		{
		case Core::CameraMovement::FORWARD:
			Position += Forward * velocity;
			break;
		case Core::CameraMovement::BACKWARD:
			Position -= Forward * velocity;
			break;
		case Core::CameraMovement::RIGHT:
			Position += Right * velocity;
			break;
		case Core::CameraMovement::LEFT:
			Position -= Right * velocity;
			break;
		default:
			break;
		}

		//Update();
	}

	void Camera::MouseMovement(float xoffset, float yoffset, bool constrainPitch)
	{
		xoffset *= MouseSensitivity;
		yoffset *= MouseSensitivity;

		Yaw += xoffset;
		Pitch += yoffset;

		if (constrainPitch) {
			if (Pitch > 89.0f) {
				Pitch = 89.0f;
			}
			if (Pitch < -89.0f) {
				Pitch = -89.0f;
			}
		}

		//Update();
	}

	void Camera::MouseScroll(float offset)
	{
		//Adjust FOV
		if (FOV >= 1.0f && FOV <= 45.0f)
			FOV -= offset;
		if (FOV <= 1.0f)
			FOV = 1.0f;
		if (FOV >= 45.0f)
			FOV = 45.0f;

		//Update();
	}


	Camera::~Camera()
	{
	}
}