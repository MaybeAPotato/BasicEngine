#include "Vertex.h"
#include "Mesh.h"
#include "Shader.h"

#include <GL/glew.h>

namespace Core {
	Vertex::Vertex()
	{
	}

	Vertex::Vertex(Mesh & m, Shader & s)
	{
	}

	Vertex::Vertex(unsigned int reserveVAO, unsigned int reserveVBO, unsigned int reserveEBO)
	{
	}


	Vertex::~Vertex()
	{
		//glDeleteVertexArrays(VAO.size(), &VAO[0]);
		//glDeleteBuffers(VBO.size(), &VBO[0]);
		//glDeleteBuffers(EBO.size(), &EBO[0]);

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

	}

	bool Vertex::Init()
	{
		return true;
	}

	void Vertex::Update()
	{
	}

	void Vertex::Render()
	{
	}

	bool Vertex::Shutdown()
	{
		return true;
	}

	//Attempt at having vectors
	/*
	//VAO
	void Vertex::ResizeVAO(unsigned int newSize)
	{
		VAO.resize(newSize);
	}

	void Vertex::AddVAO(unsigned int num)
	{
		for (unsigned int i = 0; i < num; i++) {
			VAO.push_back(NULL);
		}
	}

	void Vertex::GenVAO()
	{
		glGenVertexArrays(VAO.size(), &VAO[0]);
	}

	void Vertex::GenVAO(unsigned int index)
	{
		if(VAO[index])
		glGenVertexArrays(1,&VAO[index]);
	}

	void Vertex::BindVAO(unsigned int index)
	{
		if (VAO[index])
			glBindVertexArray(VAO[index]);
		else
			glBindVertexArray(0);
	}

	//VBO
	void Vertex::ResizeVBO(unsigned int newSize)
	{
		VBO.resize(newSize);
	}

	void Vertex::AddVBO(unsigned int num)
	{
		for (unsigned int i = 0; i < num; i++) {
			VBO.push_back(NULL);
		}
	}

	void Vertex::GenVBO()
	{
		glGenBuffers(VBO.size(), &VBO[0]);
	}

	void Vertex::GenVBO(unsigned int index)
	{
		if (VBO[index])
			glGenBuffers(1, &VBO[index]);
	}

	void Vertex::BindVBO(unsigned int index)
	{
		if (VBO[index])
			glBindBuffer(GL_ARRAY_BUFFER, VBO[index]);
		else
			glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//EBO
	void Vertex::ResizeEBO(unsigned int newSize)
	{
		EBO.resize(newSize);
	}

	void Vertex::AddEBO(unsigned int num)
	{
		for (unsigned int i = 0; i < num; i++) {
			EBO.push_back(NULL);
		}
	}

	void Vertex::GenEBO()
	{
		glGenBuffers(1, &EBO[0]);
	}

	void Vertex::GenEBO(unsigned int index)
	{
		if (EBO[index])
			glGenBuffers(EBO.size(), &EBO[0]);
	}

	void Vertex::BindEBO(unsigned int index)
	{
		if (EBO[index])
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO[index]);
		else
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	void Vertex::VertexAttributePointer(int location, int size, int type, int normalize, int stride, int offset)
	{
		glVertexAttribPointer(location, size, type, normalize, stride, (void*)offset);
		glEnableVertexAttribArray(location);
	}*/
}