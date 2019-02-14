#ifndef IMAGE_H
#define IMAGE_H

#define STB_IMAGE_IMPLEMENTATION

#include "Asset.h"
#include <vector>

namespace Core {
	class Cubemap {
		std::vector<const char*> faces;
		unsigned int cubemapID;

	public:
		Cubemap(std::vector<const char*> f);
		~Cubemap();

		inline unsigned int ID() { return cubemapID; }
		bool Init();
		void Update();
		void Render();
		bool Shutdown();
	};

	class Image : public Asset
	{
		unsigned int textureID;

		int width, height, nrChannels;

		const char* filepath;
	public:
		Image(const char* filepath);

		~Image();

		void Use();

		inline unsigned int ID() { return textureID; }
		bool Init();
		void Update();
		void Render();
		bool Shutdown();
	};
}
#endif // !IMAGE_H
