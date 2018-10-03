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

const char* skyVertex =
"#version 330 core\n"
"layout(location = 0) in vec3 aPos;\n"

"out vec3 TexCoords;\n"

"uniform mat4 projection;\n"
"uniform mat4 view;\n"

"void main() {\n"
	"TexCoords = aPos;\n"
	//View->clip(does not need to be bothered with world position)
	"vec4 pos = projection * view * vec4(aPos, 1.0);\n"
	"gl_Position = pos.xyww;\n"//Set z to w so z(depth) is always 1, reuslts in NDC
"}\n\0";

const char* skyFrag =
"#version 330 core\n"

"in vec3 TexCoords;\n"

"out vec4 FragColor;\n"

"uniform samplerCube skybox;\n"

"void main() {\n"
	"FragColor = texture(skybox, TexCoords);\n"
"}\n\0";

const char* bufferVertexSource =
"#version 330 core\n"
"layout (location = 0) in vec2 aPos;\n"
"layout (location = 1) in vec2 aTexCoords;\n"

"out vec2 TexCoords;\n"

"void main(){\n"
"gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0);\n"
"TexCoords = aTexCoords;\n"
"}\n\0";

const char* bufferFragmentSource =
"#version 330 core\n"

"in vec2 TexCoords;\n"

"out vec4 FragColor;\n"

"uniform sampler2D screenTexture;\n"

"void main(){\n"
"FragColor = texture(screenTexture,TexCoords);\n"
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

//Sky box
float skyboxVertices[] = {
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

std::vector<const char*> faces{
		"right.jpg",
		"left.jpg",
		"top.jpg",
		"bottom.jpg",
		"front.jpg",
		"back.jpg"
};


namespace Core {
	Core::Camera camera;
	Core::Camera camera2;

	Core::GameObject go;

	Core::Mesh mesh(vertices, indices);
	Core::Image image("container.jpg");
	Core::Shader shader(*vertexShader, *fragmentShader);
	Core::Vertex vertex(mesh, shader);

	//For sky box
	Core::Image cubemap(faces);
	Core::Shader skyboxShader(*skyVertex,*skyFrag);
	unsigned int skyVAO, skyVBO;

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

		image.Init();
		mesh.Init();
		shader.Init();
		vertex.Init();
		skyboxShader.Init();

		//Sky box
		glGenVertexArrays(1, &skyVAO);
		glGenBuffers(1, &skyVBO);
		glBindVertexArray(skyVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindVertexArray(0);

		skyboxShader.Use();
		skyboxShader.SetInt("skybox", 0);

		go.AddComponent(camera);
		go.AddComponent(vertex);

		shader.Use();
		shader.SetInt("texture1", 0);
		//glUniform1i(glGetUniformLocation(shader.GetShaderProgramID(), "texture1"), 0);

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

		Camera* c = static_cast<Camera*>(go.GetComponent<Camera>());

		//Keyboard input
		//Forward
		if (engineInput->IsKeyDown(SDLK_w)) {
			//camera.Keyboard(CameraMovement::FORWARD,0.16f);
			c->Keyboard(CameraMovement::FORWARD, 0.16f);
		}
		//Backward
		if (engineInput->IsKeyDown(SDLK_s)) {
			//camera.Keyboard(CameraMovement::BACKWARD, 0.16f);
			c->Keyboard(CameraMovement::BACKWARD, 0.16f);
		}
		//Right
		if (engineInput->IsKeyDown(SDLK_d)) {
			//camera.Keyboard(CameraMovement::RIGHT, 0.16f);
			c->Keyboard(CameraMovement::RIGHT, 0.16f);
		}
		//Left
		if (engineInput->IsKeyDown(SDLK_a)) {
			//camera.Keyboard(CameraMovement::LEFT, 0.16f);
			c->Keyboard(CameraMovement::LEFT, 0.16f);
		}
		//Quit
		if (engineInput->IsKeyDown(SDLK_ESCAPE)) {
			isRunning = false;
		}
		//Swap camera
		if (engineInput->WasKeyPressed(SDLK_p)) {
			go.RemoveComponent<Camera>();
			go.AddComponent(camera2);
			c = static_cast<Camera*>(go.GetComponent<Camera>());
		}

		//Camera
		if (engineInput->IsKeyDown(SDLK_LEFT)) {
			//camera.MouseMovement(-5, 0, true);
			c->MouseMovement(-5, 0, true);
		}
		if (engineInput->IsKeyDown(SDLK_RIGHT)) {
			//camera.MouseMovement(5, 0, true);
			c->MouseMovement(5, 0, true);
		}
		if (engineInput->IsKeyDown(SDLK_UP)) {
			//camera.MouseMovement(0, -5, true);
			c->MouseMovement(0, -5, true);
		}
		if (engineInput->IsKeyDown(SDLK_DOWN)) {
			//camera.MouseMovement(0, 5, true);
			c->MouseMovement(0, 5, true);
		}

		//Mouse input
		//camera.MouseMovement(engineInput->GetMouseMotionX(), -engineInput->GetMouseMotionY(),true);
		/*if(engineInput->GetMouseMotionX() != 0 || engineInput->GetMouseMotionY() != 0)
			std::cout << "X=" << engineInput->GetMouseMotionX() << " Y=" << engineInput->GetMouseMotionY() << std::endl;*/

		c->MouseMovement(engineInput->GetMouseMotionX(), engineInput->GetMouseMotionY(), true);
		c->MouseScroll(engineInput->GetMouseWheelY());

		//Joystick
		c->Controller(engineInput->GetJoyStickLeftAxisX(), engineInput->GetJoyStickLeftAxisY(), 0.16f);
		c->MouseMovement(engineInput->GetJoyStickRightAxisX(), engineInput->GetJoyStickRightAxisY(), true);

		go.Update();

		//Uniform changes
		glm::mat4 model, view, projection;

		model = glm::translate(model, glm::vec3(0.0f,0.0f,-2.0f) - c->GetPosition());
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = c->GetViewMatrix();
		projection = glm::perspective(glm::radians(c->GetFov()), engineWindow->GetWidth() / engineWindow->GetHeight(), 0.1f, 100.0f);

		shader.Use();
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);

		skyboxShader.Use();
		skyboxShader.SetMat4("view", glm::mat4(glm::mat3(c->GetViewMatrix())));
		skyboxShader.SetMat4("projection", projection);

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

		shader.Use();
		glBindTexture(GL_TEXTURE_2D, image.ID());
		glActiveTexture(GL_TEXTURE0);
		go.Render();//go->components->render

		//Sky box
		glDepthFunc(GL_LEQUAL);
		skyboxShader.Use();
		glBindVertexArray(skyVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.ID());
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);




		AssetManager::GetInstance().Render();
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
