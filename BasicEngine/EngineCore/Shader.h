#ifndef  SHADER_H
#define SHADER_H

#include "Asset.h"

//For GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <gl/glew.h>

namespace Core {
	class Shader : public Asset
	{
		unsigned int ID;
		//Source code for the vertex shader
		const char* vShaderCode;
		//Source code for the fragment shader
		const char* fShaderCode;
		
		class Mesh* mesh;
		class Vertex* vertex;

	public:
		Shader(const GLchar* vertexPath, const GLchar* fragmentPath);
		Shader(const char& vertexSource,const char& fragmentSource);
		Shader(const char& vertexSource, const char& fragmentSource, Mesh& m, Vertex& v);
		~Shader();

		bool Init() override;
		///void Update() override;
		bool Shutdown() override;
		void Render() override { glUseProgram(ID); }
		void Use();

		const unsigned int GetShaderProgramID() { return ID; }
		const char* GetVertexSource() { return vShaderCode; }
		const char* GetFragmentSource() { return fShaderCode; }

		//Get the vertex
		Vertex& GetVertex() { return *vertex; }
		//Set the vertex
		void SetVertex(Vertex& shaderVert) { vertex = &shaderVert; }

		//Get the mesh
		Mesh& GetMesh() { return *mesh; }
		//Set the mesh
		void SetMesh(Mesh& shaderMesh) { mesh = &shaderMesh; }

		//Functions for uniform
		void SetBool(const char* name, bool value);
		void SetInt(const char* name, int value);
		void SetFloat(const char* name, float value);
		
		//Vector manipulation

		void SetVec2(const char* name, float x, float y);
		void SetVec2(const char* name, glm::vec2 vec);
		void SetVec3(const char* name, float x, float y, float z);
		void SetVec3(const char* name, glm::vec3 vec);
		void SetVec4(const char* name, float x, float y, float z, float w);
		void SetVec4(const char* name, glm::vec4 vec);

		//Matrix manipulation

		void SetMat3(const char* name, glm::mat3 newMat);
		void SetMat4(const char* name, glm::mat4 newMat);


	};
}

#endif // ! SHADER_H
