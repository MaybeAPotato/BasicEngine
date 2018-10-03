#include "Vertex.h"
#include "Mesh.h"
#include "Shader.h"

#include <GL/glew.h>

#include "GameObject.h"

namespace Core {
	Vertex::Vertex()
	{
	}

	Vertex::Vertex(Mesh & m, Shader & s) : mesh(&m),shader(&s)
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
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);

		glBufferData(GL_ARRAY_BUFFER, sizeof(mesh->GetVertices()[0]) * mesh->GetVertices().size(), mesh->GetVertices().data(), GL_STATIC_DRAW);

		//Position
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		//GLenum
		//GLboolean
		glEnableVertexAttribArray(0);

		//Texture coordinate 
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);

		glBindBuffer(GL_ARRAY_BUFFER, 0);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh->GetIndices()[0]) * mesh->GetIndices().size(), mesh->GetIndices().data(), GL_STATIC_DRAW);

		glBindVertexArray(0);

		return true;
	}

	void Vertex::Update()
	{
		//shader->SetMat4("transform", parent->GetTransform());
	}

	void Vertex::Render()
	{
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
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