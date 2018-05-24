#ifndef CLOCK_H
#define CLOCK_H

#include "System.h"
#include <map>
#include <chrono>

namespace Core {
	class Clock : public System
	{
	public:
		Clock();
		~Clock();

		bool Init() override;
		void Update() override;
		void Render() override;
		bool Shutdown() override;
	};
}

#endif // !CLOCK_H
