#include "Shader.h"
#include "Mesh.h"
#include "Vertex.h"

#include <GL/glew.h>

#include <iostream>

namespace Core {

	Shader::Shader(const char& vertexSource, const char& fragmentSource) : vShaderCode(&vertexSource),fShaderCode(&fragmentSource)
	{
	}

	Shader::Shader(const char & vertexSource, const char & fragmentSource, Mesh & m, Vertex & v) : vShaderCode(&vertexSource), fShaderCode(&fragmentSource),mesh(&m),vertex(&v)
	{
	}

	Shader::~Shader()
	{
		//glDeleteProgram(ID);
		delete mesh;
		mesh = nullptr;

		delete vertex;
		vertex = nullptr;
	}
	bool Shader::Init()
	{
		int vertex, fragment;
		int success;
		char infoLog[512];

		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);

		glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILURE\n" << infoLog << std::endl;
			return false;
		}

		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);

		glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
		if (!success) {
			glGetShaderInfoLog(vertex, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILURE\n" << infoLog << std::endl;
			return false;
		}

		ID = glCreateProgram();

		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);

		glGetProgramiv(ID, GL_LINK_STATUS, &success);
		if (!success) {
			glGetProgramInfoLog(ID, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILURE\n" << infoLog << std::endl;
			return false;
		}

		glDeleteShader(vertex);
		glDeleteShader(fragment);


		return true;
	}
	bool Shader::Shutdown()
	{
		return true;
	}
	void Shader::Use()
	{
		glUseProgram(ID);
	}
	void Shader::SetBool(const char * name, bool value)
	{
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
	void Shader::SetInt(const char * name, int value)
	{
		glUniform1i(glGetUniformLocation(ID, name), value);
	}
	void Shader::SetFloat(const char * name, float value)
	{
		glUniform1f(glGetUniformLocation(ID, name), value);
	}

	void Shader::SetVec2(const char * name, float x, float y)
	{
		glUniform2fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(glm::vec2(x, y)));
	}

	void Shader::SetVec2(const char * name, glm::vec2 vec)
	{
		glUniform2fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(vec));
	}

	void Shader::SetVec3(const char * name, float x, float y, float z)
	{
		glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(glm::vec3(x, y, z)));
	}

	void Shader::SetVec3(const char * name, glm::vec3 vec)
	{
		glUniform3fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(glm::vec3(vec)));

	}

	void Shader::SetVec4(const char * name, float x, float y, float z, float w)
	{
		glUniform4fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(glm::vec4(x, y, z, w)));

	}

	void Shader::SetVec4(const char * name, glm::vec4 vec)
	{
		glUniform4fv(glGetUniformLocation(ID, name), 1, glm::value_ptr(glm::vec4(vec)));
	}

	void Shader::SetMat3(const char * name, glm::mat3 newMat)
	{
		glUniformMatrix3fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(newMat));
	}

	void Shader::SetMat4(const char * name, glm::mat4 newMat)
	{
		glUniformMatrix4fv(glGetUniformLocation(ID, name), 1, GL_FALSE, glm::value_ptr(newMat));
	}
}
