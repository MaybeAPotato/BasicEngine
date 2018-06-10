#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Core {

	enum class CameraMovement : unsigned __int8 {
		FORWARD,
		BACKWARD,
		RIGHT,
		LEFT,
		TOTAL
	};

	class Camera
	{
		//Default values
		const float YAW = -90.0f;
		const float PITCH = 0.0f;
		const float SPEED = 2.5f;
		const float MOUSE_SENSITIVITY = 0.1f;
		const float FIELD_OF_VIEW = 45.0f;

		glm::vec3 Position;
		glm::vec3 Forward;
		glm::vec3 Up;
		glm::vec3 Right;
		glm::vec3 WorldUp;

		//Euler angles
		float Yaw;
		float Pitch;

		float MovementSpeed;
		float MouseSensitivity;
		float FOV;

		void Update();

	public:
		Camera();
		Camera(glm::vec3 pos,glm::vec3 forward,glm::vec3 up,glm::vec3 right,glm::vec3 worldup,float yaw,float pitch,float movespeed,float sensitivity,float fov);
		glm::mat4 GetViewMatrix() { return glm::lookAt(Position, Position + Forward, Up); /*position,forward pointing forward(-Z axis),up*/}
		void Keyboard(CameraMovement direction, float deltaTime);
		void MouseMovement(float xoffset, float yoffset, bool constrainPitch = true);
		void MouseScroll(float offset);

		~Camera();
	};

}
#endif // !CAMERA_H