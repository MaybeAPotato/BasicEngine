#ifndef IMAGE_H
#define IMAGE_H

#include "Asset.h"

namespace Core {
	class Image : public Asset
	{
		unsigned int textureID;

		int width, height, nrChannels;

		const char* filepath;
	public:
		Image(const char* filepath);
		~Image();

		void Use();

		bool Init() override;
		void Update() override;
		void Render() override;
		bool Shutdown() override;
	};
}
#endif // !IMAGE_H
