#ifndef SYSTEM_UI_H
#define SYSTEM_UI_H

#include "System.h"

namespace Core {
	class SystemUI : public System
	{
	public:
		SystemUI();
		~SystemUI();

		bool Init() override;
		void Update() override;
		void Render() override;
		bool Shutdown() override;
	};
}
#endif // !SYSTEM_UI_H
