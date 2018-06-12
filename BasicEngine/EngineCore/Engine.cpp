#include "Engine.h"
#include "LogManager.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

//Asset
#include "AssetManager.h"
#include "Asset.h"
#include "Shader.h"
#include "Mesh.h"
#include "Image.h"

//Component
#include "Vertex.h"
#include "Camera.h"

//System
#include "SystemManager.h"
#include "Window.h"
#include "Graphic.h"
#include "Clock.h"
#include "SystemUI.h"
#include "Input.h"
#include "Camera.h"

#include "GameObject.h"

//For glm
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_sdl_gl3.h"

const char* vertexShader =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n" //Helps openGL know where to put variable
"layout(location = 1) in vec2 aTexCoord;\n"

"out vec2 TexCoord;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
//"uniform mat4 transform;\n"

"void main(){\n"
"gl_Position = projection * view * model * vec4(aPos,1.0);\n"//Saved variable from openGL
//"gl_Position = transform * vec4(aPos,1.0);\n"
"TexCoord = aTexCoord;\n"
"}\n\0";

const char* fragmentShader =
"#version 330 core\n"
"out vec4 FragColor;\n"

"in vec2 TexCoord;\n"

"uniform sampler2D texture1;\n"

"void main(){\n"
"FragColor = texture(texture1,TexCoord);\n"
"}\n\0";

const char* meshVertices =
"v 0.5f, 0.5f, 0.0f\n"
"v 0.5f, -0.5f, 0.0f\n"
"v -0.5, -0.5f, 0.0f\n"
"v -0.5f, 0.5f, 0.0f\n"
"i 0, 1, 3\n"
"i 1, 2, 3\n"
;

std::vector<float>vertices = { 0.5f, 0.5f, 0.0f,
0.5f, -0.5f,0.0f,
-0.5, -0.5f,0.0f,
-0.5f,0.5f,0.0f };

std::vector<unsigned int>indices = { 0, 1, 3,
1,2,3 };

float textCoords[] = {
	0.0f,0.0f,
	1.0f,0.0f,
	0.0f,1.0f,
	1.0f,1.0f
};


namespace Core {
	Core::GameObject go;

	Core::Camera camera;

	Core::Mesh mesh(vertices, indices);
	Core::Image image("container.jpg");
	Core::Shader shader(*vertexShader, *fragmentShader);
	Core::Vertex vertex(mesh, shader);

	Engine::Engine() : isRunning(true),engineWindow(new Window()),engineGraphic(new Graphic()),engineClock(new Clock()),engineUI(new SystemUI()),engineInput(new Input()){
		SystemManager::GetInstance().AddSystem(*engineWindow);
		SystemManager::GetInstance().AddSystem(*engineClock);
		SystemManager::GetInstance().AddSystem(*engineInput);
		SystemManager::GetInstance().AddSystem(*engineGraphic);
		SystemManager::GetInstance().AddSystem(*engineUI);
	}

	Engine::~Engine(){
		#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine shutdown");
		#endif
		delete engineWindow;
		engineWindow = nullptr;

		delete engineGraphic;
		engineGraphic = nullptr;

		delete engineClock;
		engineClock = nullptr;

		delete engineUI;
		engineUI = nullptr;

		delete engineInput;
		engineInput = nullptr;

		/*glDeleteVertexArrays(1,&VAO);
		glDeleteBuffers(1,&VBO);
		glDeleteBuffers(1, &EBO);*/

		#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Shutdown");
		#endif
	}
	
	int Engine::Init(){
		//auto start = std::chrono::high_resolution_clock().now();
		//Get instance of log manager
		LogManager::GetInstance();

		//Used to check init success
		int success = 0;
		#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine init");
		#endif

		if (!SystemManager::GetInstance().Init()) {
		#if _DEBUG
			LogManager::Log(Core::Loglevel::FATAL,"ERROR::INIT::SYSTEM_MANAGER");
		#endif
			success = 1;
		}

		if (!AssetManager::GetInstance().Init()) {
		#if _DEBUG
			LogManager::Log(Core::Loglevel::FATAL, "ERROR::INIT::ASSET_MANAGER");
		#endif
			success = 1;
		}

		camera.Init();

		mesh.Init();
		shader.Init();
		image.Init();
		vertex.Init();

		go.AddComponent(camera);
		go.AddComponent(vertex);

		glUniform1i(glGetUniformLocation(shader.GetShaderProgramID(), "texture1"), 0);

		//auto end = std::chrono::high_resolution_clock().now();
		//auto durationMS = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

		//std::cout << "Engine init took " << durationMS.count() << " ms" << std::endl;

		return 0;
	}

	bool show_demo_window = true;
	bool show_another_window = true;
	float clear_color[4] = { 0.45f,0.55f,0.60f,1.0f };

	void Engine::Run()
	{
		#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine run");
		#endif
		//Infinite engine loop
		while (isRunning) {
			Update();
			Render();
		}

		Shutdown();
	}

	void Engine::Update(){
		//Event handling
		//const auto start = std::chrono::high_resolution_clock().now();

		//LARGE_INTEGER t;
		//QueryPerformanceFrequency(&t);

		SystemManager::GetInstance().Update();


		go.Update();

		//Keyboard input
		//Forward
		if (engineInput->IsKeyDown(SDLK_w)) {
			camera.Keyboard(CameraMovement::FORWARD,0.16f);
		}
		//Backward
		if (engineInput->IsKeyDown(SDLK_s)) {
			camera.Keyboard(CameraMovement::BACKWARD, 0.16f);
		}
		//Right
		if (engineInput->IsKeyDown(SDLK_d)) {
			camera.Keyboard(CameraMovement::RIGHT, 0.16f);
		}
		//Left
		if (engineInput->IsKeyDown(SDLK_a)) {
			camera.Keyboard(CameraMovement::LEFT, 0.16f);
		}

		//Camera
		if (engineInput->IsKeyDown(SDLK_LEFT)) {
			camera.MouseMovement(-5, 0, true);
		}
		if (engineInput->IsKeyDown(SDLK_RIGHT)) {
			camera.MouseMovement(5, 0, true);
		}
		if (engineInput->IsKeyDown(SDLK_UP)) {
			camera.MouseMovement(0, 5, true);
		}
		if (engineInput->IsKeyDown(SDLK_DOWN)) {
			camera.MouseMovement(0, -5, true);
		}
		

		//Mouse input
		//if (engineInput->GetMouseMotionX() > 0 || engineInput->GetMouseMotionY() > 0) {
		//	camera.MouseMovement(engineInput->GetMouseMotionX(), engineInput->GetMouseMotionY(),true);
		//}

		//Uniform changes
		glm::mat4 model, view, projection;

		model = glm::translate(model, -camera.GetPosition());
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = camera.GetViewMatrix();
		projection = glm::perspective(glm::radians(camera.GetFov()), 800.0f / 600.0f, 0.1f, 100.0f);

		//int modelLoc = glGetUniformLocation(shader.GetShaderProgramID(), "model");
		//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
		shader.SetMat4("model", model);

		//int viewLoc = glGetUniformLocation(shader.GetShaderProgramID(), "view");
		//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
		shader.SetMat4("view", view);

		//int projLoc = glGetUniformLocation(shader.GetShaderProgramID(), "projection");
		//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
		shader.SetMat4("projection", projection);

		if (engineInput->QuitRequested()) {
			isRunning = false;
		}

		AssetManager::GetInstance().Update();

		//const auto end = std::chrono::high_resolution_clock().now();
		//const auto durationMS = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		//std::cout << durationMS.count() << " ms" << std::endl;
	}

	void Engine::Render() {
		SystemManager::GetInstance().Render();
		go.Render();
		AssetManager::GetInstance().Render();

		//static_cast<Shader*>(AssetManager::GetInstance().GetAsset("Shader"))->Use();
		//glBindVertexArray(VAO);
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}

	int Engine::Shutdown()
	{
		#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Engine shutdown");
		#endif
		int success = 0;

		#if _DEBUG
		LogManager::Log(Core::Loglevel::DEFAULT, "Systems shutdown");
		#endif
		//If the window failed to shutdown
		if (!SystemManager::GetInstance().Shutdown()) {
		#if _DEBUG
			LogManager::Log(Core::Loglevel::FATAL, "Failed to properly shutdown a system");
		#endif
			success = 1;
		}

		if (!AssetManager::GetInstance().Shutdown()) {
		#if _DEBUG
			LogManager::Log(Core::Loglevel::FATAL, "Failed to properly shutdown an asset");
		#endif
			success = 1;
		}

		go.Shutdown();

		return success;
	}
}
