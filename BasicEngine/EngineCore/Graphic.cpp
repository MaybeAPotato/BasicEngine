#include "Graphic.h"
#include "LogManager.h"
#include <GL/glew.h>

namespace Core{
	Graphic::Graphic() : System(SystemType::GRAPHICS)
	{
	}
	Graphic::~Graphic()
	{
	}

	//Initialize openGL
	bool Graphic::InitOpenGL()
	{
		GLenum error = glewInit();

		if (error != GLEW_OK) {
			LogManager::Log(Loglevel::ERROR,"Failed to init Glew");
			return false;
		}

		

		return true;
	}
	bool Graphic::ShutdownOpenGL()
	{
		return true;
	}
	bool Graphic::Init()
	{
		if (!InitOpenGL()) {
			return false;
		}

		//Background colour
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

		return true;
	}
	void Graphic::Update()
	{
	}
	void Graphic::Render()
	{
		//GL
		//Clear these whenever you draw
		glClearDepth(1.0f);
		//Buffers that hold informtaion for colour
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glEnableClientState(GL_COLOR_ARRAY);

		//TODO: remove this by adding a mesh
		//open pipe method - terrible performance
		//Starts drawing
		/*glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0, 0.0f);
		glVertex2f(0, 0);
		glVertex2f(0, 500);
		glVertex2f(500, 500);*/
		//Ends drawing
		glEnd();
	}
	bool Graphic::Shutdown()
	{
		return true;
	}
}
