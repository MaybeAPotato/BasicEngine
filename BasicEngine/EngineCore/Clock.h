#ifndef CLOCK_H
#define CLOCK_H

#include "System.h"
#include <map>
#include <chrono>

namespace Core {
	class Clock : public System
	{
		//How many frames passed
		static uint64_t frameCounter;
		//How many seconds passed
		static double elapsedSeconds;
		//Clock used to track time
		static std::chrono::high_resolution_clock clock;

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
