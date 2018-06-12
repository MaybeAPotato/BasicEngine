#ifndef MESH_H
#define MESH_H

#include "Asset.h"
#include <vector>

namespace Core {
	class Mesh : public Asset
	{
		std::vector<float> vertices;
		std::vector<float> vertNormals;
		std::vector<float> vertFaces;
		std::vector<float> textCoords;
		std::vector<unsigned int> indices;


	public:
		//A large file of data
		Mesh(const char* data);
		//A series of vertices and indices
		//Mesh(float* v, unsigned int* i);
		Mesh(float* v, int vSize, unsigned int* i, int iSize);
		Mesh(const std::vector<float>& v, const std::vector<unsigned int>& i);
		std::vector<float>& GetVertices() { return vertices; }
		std::vector<float>& GetVertNormals() { return vertNormals; }
		std::vector<float>& GetVertFaces() { return vertFaces; }
		std::vector<float>& GetTextCoords() { return textCoords; }
		std::vector<unsigned int>& GetIndices() { return indices; }

		~Mesh();
	};
}
#endif
