#include "Engine.h"
#include "LogManager.h"

#include <SDL/SDL.h>
#include <GL/glew.h>

//Asset
#include "AssetManager.h"
#include "Asset.h"
#include "Shader.h"
#include "Vertex.h"
#include "Mesh.h"
#include "Image.h"

//System
#include "SystemManager.h"
#include "Window.h"
#include "Graphic.h"
#include "Clock.h"
#include "SystemUI.h"
#include "Input.h"
#include "Camera.h"

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

"void main(){\n"
"gl_Position = vec4(aPos,1.0);\n"//Saved variable from openGL
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
"v -1.0 -1.0 1.0\n"
"v -1.0 1.0 1.0\n"
"v -1.0 -1.0 -1.0\n"
"v -1.0 1.0 -1.0\n"
"v 1.0 -1.0 1.0\n"
"v 1.0 1.0 1.0\n"
"v 1.0 -1.0 -1.0\n"
"v 1.0 1.0 -1.0\n"
;

float vertices[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f,0.0f,
	-0.5, -0.5f,0.0f,
	-0.5f,0.5f,0.0f
};

unsigned int indices[] = {
	0, 1, 3,
	1,2,3
};

unsigned int VAO, VBO, EBO;

glm::mat4 model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
glm::mat4 view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);

namespace Core {
	Engine::Engine() : isRunning(true),engineWindow(new Window()),engineGraphic(new Graphic()),engineClock(new Clock()),engineUI(new SystemUI()),engineInput(new Input()){
		SystemManager::GetInstance().AddSystem(*engineWindow);
		SystemManager::GetInstance().AddSystem(*engineClock);
		SystemManager::GetInstance().AddSystem(*engineInput);
		SystemManager::GetInstance().AddSystem(*engineGraphic);
		SystemManager::GetInstance().AddSystem(*engineUI);

		Core::Mesh* mesh = new Mesh(meshVertices);
		Core::Image* image = new Image("container.jpg");
		//Core::Vertex* vert = new Vertex(1, 1, 1);
		/*vert->BindVAO(0);
		vert->BindVBO(0);
		vert->BufferData(vertices, Core::DataType::STATIC);
		vert->VertexAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);
		vert->BindVBO(-1);
		vert->BindEBO(0);
		vert->BufferElement(indices, Core::DataType::STATIC);
		vert->BindVAO(-1);*/

		Core::Shader* shader =  new Shader(*vertexShader, *fragmentShader);
		AssetManager::GetInstance().AddAsset("Shader",shader);
		AssetManager::GetInstance().AddAsset("Image", image);

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

		glDeleteVertexArrays(1,&VAO);
		glDeleteBuffers(1,&VBO);
		glDeleteBuffers(1, &EBO);

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

		Shader* s = dynamic_cast<Shader*>(AssetManager::GetInstance().GetAsset("Shader"));

		//Use shader program
		s->Use();

		//VAO,VBO
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER,VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			//GLenum
			//GLboolean
		glEnableVertexAttribArray(0);

		//Texture coordinate 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER,0);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);

		glUniform1i(glGetUniformLocation(s->GetShaderProgramID(), "texture1"), 0);

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

		/*
		//Forward
		if (engineInput->IsKeyDown(SDLK_w)) {
			LogManager::GetInstance().Log(Loglevel::DEFAULT, "Forward");
			engineCamera->Keyboard(CameraMovement::FORWARD,0.16f);
		}
		//Backward
		if (engineInput->IsKeyDown(SDLK_s)) {
			LogManager::GetInstance().Log(Loglevel::DEFAULT, "Backward");
			engineCamera->Keyboard(CameraMovement::BACKWARD, 0.16f);
		}
		//Right
		if (engineInput->IsKeyDown(SDLK_d)) {
			LogManager::GetInstance().Log(Loglevel::DEFAULT, "Right");
			engineCamera->Keyboard(CameraMovement::RIGHT, 0.16f);
		}
		//Left
		if (engineInput->IsKeyDown(SDLK_a)) {
			LogManager::GetInstance().Log(Loglevel::DEFAULT, "Left");
			engineCamera->Keyboard(CameraMovement::LEFT, 0.16f);
		}*/

		/*Shader* s = dynamic_cast<Shader*>(AssetManager::GetInstance().GetAsset("Shader"));
		int modelMat = glGetUniformLocation(s->GetShaderProgramID(), "model");
		glUniformMatrix4fv(modelMat, 1, GL_FALSE, glm::value_ptr(model));
		int viewMat = glGetUniformLocation(s->GetShaderProgramID(),"view");
		glUniformMatrix4fv(viewMat, 1, GL_FALSE, glm::value_ptr(engineCamera->GetViewMatrix()));
		int projMat = glGetUniformLocation(s->GetShaderProgramID(), "projection");
		glUniformMatrix4fv(projMat, 1, GL_FALSE, glm::value_ptr(projection));*/

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
		AssetManager::GetInstance().Render();

		static_cast<Shader*>(AssetManager::GetInstance().GetAsset("Shader"))->Use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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



		return success;
	}
}
