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
		std::vector<int> indices;


	public:
		//A large file of data
		Mesh(const char* data);
		//A series of vertices and indices
		Mesh(float* v, int* i);
		std::vector<float>& GetVertices() { return vertices; }
		std::vector<float>& GetVertNormals() { return vertNormals; }
		std::vector<float>& GetVertFaces() { return vertFaces; }
		std::vector<float>& GetTextCoords() { return textCoords; }
		std::vector<int>& GetIndices() { return indices; }

		~Mesh();
	};
}
#endif
