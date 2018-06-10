#ifndef VERTEX_H
#define VERTEX_H

#include <vector>
#include "Component.h"

namespace Core {
	enum class DataType : unsigned __int8 {
		STATIC, //0x88E4
		DYNAMIC,//0x88E8
		CONSTANT,//0x88E0
		TOTAL
	};

	//Vertex array object,vertex buffer objects, and element buffer object
	class Vertex : public Component
	{
		//Vertex array object
		unsigned int VAO;
		//std::vector<unsigned int>VAO;

		//Vertex buffer object
		unsigned int VBO;
		//std::vector<unsigned int>VBO;

		//Element buffer objects
		unsigned int EBO;
		//std::vector<unsigned int>EBO;

	public:
		Vertex();
		Vertex(class Mesh& m, class Shader& s);
		Vertex(unsigned int reserveVAO, unsigned int reserveVBO, unsigned int reserveEBO);

		~Vertex();


		bool Init() override;
		void Update() override;
		void Render() override;
		bool Shutdown() override;

		//Attempt at vectors
		/*
		//VAO
		void ResizeVAO(unsigned int newSize);
		void AddVAO(unsigned int num);
		//Gen for all VAOs
		void GenVAO();
		void GenVAO(unsigned int index);
		void BindVAO(unsigned int index);

		//VBO
		void ResizeVBO(unsigned int newSize);
		void AddVBO(unsigned int num);
		//Gen for all VBOs
		void GenVBO();
		void GenVBO(unsigned int index);
		template<typename T>
		inline void BufferData(T & data, DataType type)
		{
			switch (type) {
			case(DataType::STATIC):
				glBufferData(GL_ARRAY_BUFFER, sizeof(T), data, GL_STATIC_DRAW);
				break;
			case(DataType::DYNAMIC):
				glBufferData(GL_ARRAY_BUFFER, sizeof(T), data, GL_DYNAMIC_DRAW);
				break;
			case(DataType::CONSTANT):
				glBufferData(GL_ARRAY_BUFFER, sizeof(T), data, GL_STREAM_DRAW);
				break;
			}
		}
		void BindVBO(unsigned int index);

		//EBO
		void ResizeEBO(unsigned int newSize);
		void AddEBO(unsigned int num);
		//Gen for all EBOs
		void GenEBO();
		void GenEBO(unsigned int index);
		template<typename T>
		void BufferElement(T & data, DataType type)
		{
			switch (type) {
			case(DataType::STATIC):
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T), data, GL_STATIC_DRAW);
				break;
			case(DataType::DYNAMIC):
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T), data, GL_DYNAMIC_DRAW);
				break;
			case(DataType::CONSTANT):
				glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(T), data, GL_STREAM_DRAW);
				break;
			}
		}
		void BindEBO(unsigned int index);

		void VertexAttributePointer(int location, int size, int type, int normalize, int stride, int offset);*/

	};
}
#endif // !VERTEX_H
