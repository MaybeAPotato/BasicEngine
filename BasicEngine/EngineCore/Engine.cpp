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
"layout(location = 1) in vec3 aNormal;\n"
//"layout(location = 2) in vec2 aTexCoords;\n"

"out vec2 TexCoord;\n"
"out vec3 Normal;\n"
"out vec3 Position;\n"

"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
//"uniform mat4 transform;\n"

"void main(){\n"
"mat3 normalMatrix = mat3(transpose(inverse(model)));\n"
"Normal =  normalMatrix * aNormal;"
"TexCoord = aPos.xy;\n"
"Position = vec3( model * vec4(aPos,1.0));\n"
"gl_Position = projection * view * model * vec4(aPos,1.0);\n"//Saved variable from openGL
//"gl_Position = transform * vec4(aPos,1.0);\n"
"}\n\0";

const char* fragmentShader =
"#version 330 core\n"
"out vec4 FragColor;\n"

"in vec3 Position;\n"
"in vec2 TexCoord;\n"
"in vec3 Normal;\n"

"uniform sampler2D texture1;\n"
"uniform samplerCube skybox;\n"
"uniform vec3 cameraPos;\n"

"void main(){\n"
"float ratio = 1.00/1.52;\n"
"vec3 I = normalize(Position - cameraPos);\n"

//v_refract = (m1/m2) * I + ((m1/m2) * cos(theta_1) - cos(theta_2)) * normal
//where theta_1 is incidence angle and theta_2 is the refracted angle
//v_reflect = I + 2 * cos(theta_1) * normal
//cos(theta_1) = -normal * I; //must always be positive
//"vec3 R = ratio * I + (ratio * c - sqrt(1 - (ratio * ratio) * (I - c * c))) * Normal;\n"

"vec3 R = refract(I,normalize(Normal),ratio);\n"
"FragColor = vec4(texture(skybox,R).rgb,1.0);\n"
//"FragColor = texture(texture1,TexCoord);\n"
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

"out vec4 FragColor;\n"

"in vec3 TexCoords;\n"

"uniform samplerCube skybox;\n"

"void main() {\n"
	"FragColor = texture(skybox, TexCoords);\n"
	//"FragColor = vec4(1.0,0.0,0.0,0.0);\n"
"}\n\0";

std::vector<float>vertices = { 0.5f, 0.5f, 0.0f,
0.5f, -0.5f,0.0f,
-0.5, -0.5f,0.0f,
-0.5f,0.5f,0.0f };

float vesices[] = { 0.5f, 0.5f, 0.0f,
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

//For a cube with normals
float cubeVertices[] = {
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
	-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,

	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,  0.0f,  0.0f, 1.0f,

	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
	-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
	-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
	-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
};

glm::vec4 lightPos = glm::vec4(0.0f,0.0f,0.0f,00.0f);

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
		"posx.jpg",//right
		"negx.jpg",//left
		"posy.jpg",//top
		"negy.jpg",//bottom
		"posz.jpg",//front
		"negz.jpg"//back
};


namespace Core {
	Core::Camera camera;
	Core::Camera camera2;

	Core::GameObject go;

	Core::Image image("container.jpg");
	Core::Shader shader(*vertexShader, *fragmentShader);

	//For sky box
	Core::Cubemap cubemap(faces);
	Core::Shader skyboxShader(*skyVertex,*skyFrag);
	unsigned int skyVAO, skyVBO;

	//For cube
	//Core::Shader cubeShader("toonShaderVertex.vs", "toonShaderFragment.fs");
	unsigned int cubeVAO, cubeVBO;

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
		engineWindow = nullptr;
		delete engineWindow;

		engineGraphic = nullptr;
		delete engineGraphic;

		engineClock = nullptr;
		delete engineClock;

		engineUI = nullptr;
		delete engineUI;

		engineInput = nullptr;
		delete engineInput;
		
		glDeleteVertexArrays(1,&skyVAO);
		glDeleteBuffers(1,&skyVBO);

		glDeleteVertexArrays(1, &cubeVAO);
		glDeleteBuffers(1, &cubeVBO);

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
		shader.Init();
		skyboxShader.Init();
		cubemap.Init();

		glViewport(0, 0, engineWindow->GetWidth(), engineWindow->GetHeight());

		//Cube 
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		glBindVertexArray(cubeVAO);
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVertices), cubeVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);//Normals
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
		//glEnableVertexAttribArray(2);//Texture
		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
		glBindVertexArray(0);

		//Sky box
		glGenVertexArrays(1, &skyVAO);
		glGenBuffers(1, &skyVBO);
		glBindVertexArray(skyVAO);
		glBindBuffer(GL_ARRAY_BUFFER, skyVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glBindVertexArray(0);

		go.AddComponent(camera);

		skyboxShader.Use();
		skyboxShader.SetInt("skybox", 0);

		shader.Use();
		//shader.SetInt("texture1", 0);
		shader.SetInt("skybox", 0);
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
		c->MouseMovement(engineInput->GetJoyStickRightAxisX(), engineInput->GetJoyStickRightAxisY());

		//Also updates the camera
		go.Update();

		//Uniform changes
		glm::mat4 model, view, projection;

		model = glm::translate(model, glm::vec3(0.0f,0.0f,-4.0f) - c->GetPosition());
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
		view = c->GetViewMatrix();
		projection = glm::perspective(glm::radians(c->GetFov()), engineWindow->GetWidth() / engineWindow->GetHeight(), 0.1f, 100.0f);

		shader.Use();
		shader.SetMat4("model", model);
		shader.SetMat4("view", view);
		shader.SetMat4("projection", projection);
		shader.SetVec3("cameraPos", c->GetPosition());

		skyboxShader.Use();
		skyboxShader.SetMat4("view",glm::mat4(glm::mat3(view)));
		skyboxShader.SetMat4("projection", projection);

		if (engineInput->QuitRequested()) {
			isRunning = false;
		}
	}

	void Engine::Render() {
		SystemManager::GetInstance().Render();

		
		shader.Use();
		glBindVertexArray(cubeVAO);
		glBindTexture(GL_TEXTURE_2D, image.ID());
		glActiveTexture(GL_TEXTURE0);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);

		go.Render();

		//Sky box
		glDepthFunc(GL_LEQUAL);
		//glDisable(GL_DEPTH_TEST | GL_CULL_FACE);
		skyboxShader.Use();
		glBindVertexArray(skyVAO);
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap.ID());
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);
		glDepthFunc(GL_LESS);
		//glEnable(GL_DEPTH_TEST | GL_CULL_FACE);
		//AssetManager::GetInstance().Render();
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
		LogManager::Log(Core::Loglevel::DEFAULT, "Assets shutdown");
		if (!AssetManager::GetInstance().Shutdown()) {
		#if _DEBUG
			LogManager::Log(Core::Loglevel::FATAL, "Failed to properly shutdown an asset");
		#endif
			success = 1;
		}

		go.Shutdown();
		camera.Shutdown();
		camera2.Shutdown();

		return success;
	}
}
