#ifndef GRAPHIC_H
#define GRAPHIC_H

#include "System.h"

namespace Core{
	class Graphic : public System
	{
		bool InitOpenGL();
		bool ShutdownOpenGL();
	public:
		Graphic();
		~Graphic();

		virtual bool Init() override;
		virtual void Update() override;
		virtual void Render() override;
		virtual bool Shutdown() override;
	};
}
#endif // !GRAPHIC_H
