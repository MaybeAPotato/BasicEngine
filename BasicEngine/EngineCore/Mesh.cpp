#include "Mesh.h"
#include <iostream>
#include <sstream>

namespace Core {

	Core::Mesh::Mesh(const char * data)
	{
		std::istringstream stream(data);
		std::string line;

		//Loop through each line
		while (std::getline(stream,line)) {
			char c;
			stream.get(c);
			//Seeing as the first value is the char
			std::string numStream = line.substr(2, line.length());
			int pos = 0;
			switch (c)
			{
			//Vertex
			case('v'):
				while (numStream.size() > 0) {
					pos = numStream.find(" ");
					pos = pos == std::string::npos ? numStream.size()-1 : pos;
					std::string token = numStream.substr(0, pos);
					vertices.push_back(std::stof(token.c_str()));
					textCoords.push_back(std::stof(token.c_str()));
					numStream.erase(0, pos + 1);
				}

				break;
			//Vertex normal
			case('vn'):
				while (numStream.size() > 0) {
					pos = numStream.find(" ");
					pos = pos == std::string::npos ? numStream.size() - 1 : pos;
					std::string token = numStream.substr(0, pos);
					vertNormals.push_back(std::stof(token.c_str()));
					numStream.erase(0, pos);
				}

				break;
			//Texture coordinates
			//case('tx'):
			//	textCoords += line + "\n";
			//	break;
			//Face(series of vertices)
			case('f'):
				while (numStream.size() > 0) {
					pos = numStream.find(" ");
					pos = pos == std::string::npos ? numStream.size() - 1 : pos;
					std::string token = numStream.substr(0, pos);
					vertFaces.push_back(std::stof(token.c_str()));
					numStream.erase(0, pos);
				}

				break;
			//Indices(guide points)
			case('i'):
				while (numStream.size() > 0) {
					pos = numStream.find(" ");
					pos = pos == std::string::npos ? numStream.size() - 1 : pos;
					std::string token = numStream.substr(0, pos);
					indices.push_back(std::stof(token.c_str()));
					numStream.erase(0, pos);
				}
				break;
			default:
				break;
			}
		}
	}

	Mesh::Mesh(float * v, int vSize, unsigned int * i, int iSize)
	{
		vertices.reserve(vSize);
		indices.reserve(iSize);
		for (int f = 0; f < vSize; f++) {
			vertices.insert(vertices.begin() + f, v[f]);
		}
		for (int f = 0; f < iSize; f++) {
			indices.insert(indices.begin() + f, i[f]);
		}

	}

	Mesh::Mesh(const std::vector<float>& v, const std::vector<unsigned int>& i)
	{
		vertices.reserve(v.size());
		vertices = v;
		indices.reserve(i.size());
		indices = i;
	}



	Mesh::~Mesh()
	{
		vertices.clear();
		vertNormals.clear();
		vertFaces.clear();
		textCoords.clear();
		indices.clear();
	}
}