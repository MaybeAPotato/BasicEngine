#include "Image.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <GL/glew.h>

namespace Core {

	Image::Image(const char* filepath) : filepath(filepath)
	{

	}


	Image::~Image()
	{
	}
	bool Image::Init()
	{
		unsigned char *data = stbi_load(filepath, &width, &height, &nrChannels, 0);

		glGenTextures(1, &textureID);

		glActiveTexture(GL_TEXTURE0);

		glBindTexture(GL_TEXTURE_2D, textureID);

		//Wrapping
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//Filtering
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_set_flip_vertically_on_load(true);

		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
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
	}
	bool Image::Shutdown()
	{
		return true;
	}
}
