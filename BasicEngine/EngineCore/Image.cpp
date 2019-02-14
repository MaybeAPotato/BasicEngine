#include "Image.h"

#include "stb_image.h"

#include <iostream>
#include <GL/glew.h>

namespace Core {
	Image::Image(const char* filepath) : filepath(filepath)
	{

	}

	Cubemap::Cubemap(std::vector<const char*> f) : faces(f)
	{

	}

	Cubemap::~Cubemap()
	{
	}

	bool Cubemap::Init()
	{
		int w, h, nr;

		GLenum format;

		unsigned char* data;

		glGenTextures(1, &cubemapID);
		
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
		
		stbi_set_flip_vertically_on_load(false);

		//Increment faces
		for (GLuint i = 0; i < faces.size(); i++) {
			data = stbi_load(faces[i], &w, &h, &nr, 0);

			switch (nr) {
			case(1):
				format = GL_RED;
				break;
			case(3):
				format = GL_RGB;
				break;
			case(4):
				format = GL_RGBA;
				break;
			}

			if (data) {
				glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, format, w, h, 0, format, GL_UNSIGNED_BYTE, data);
			}
			else {
				std::cout << "CUBEMAP TEXTURE FAILED TO LOAD AT PATH: " << &faces[i] << std::endl;
			}

			stbi_image_free(data);
		}

		//Wrapping
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);//R being z-axis?
		//Filtering
		//Set to clamp do to hardware limitations
		//Returns edge values when sampling between faces
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		return true;
	}

	void Cubemap::Update()
	{
	}

	void Cubemap::Render()
	{
		glBindTexture(GL_TEXTURE_CUBE_MAP, cubemapID);
		glActiveTexture(GL_TEXTURE0);
	}

	bool Cubemap::Shutdown()
	{
		return true;
	}


	Image::~Image()
	{
	}
	void Image::Use()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
	}
	bool Image::Init()
	{
		stbi_set_flip_vertically_on_load(true);

		unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);

		if (data) {
			GLenum format;

			switch (nrChannels) {
			case(1):
				format = GL_RED;
				break;
			case(3):
				format = GL_RGB;
				break;
			case(4):
				format = GL_RGBA;
				break;
			}

			glGenTextures(1, &textureID);

			glBindTexture(GL_TEXTURE_2D, textureID);

			glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

			glActiveTexture(GL_TEXTURE0);

			//Wrapping
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

			//Filtering
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		}
		else {
			printf("FAILED TO LOAD IMAGE\n");
			return false;
		}

		stbi_image_free(data);

		return true;
	}
	void Image::Update()
	{
	}
	void Image::Render()
	{
		glBindTexture(GL_TEXTURE_2D, textureID);
		glActiveTexture(GL_TEXTURE0);
	}
	bool Image::Shutdown()
	{
		return true;
	}
}
