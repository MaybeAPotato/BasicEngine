#include "Clock.h"

namespace Core {
	Clock::Clock() : System(SystemType::CLOCK)
	{
	}

	Clock::~Clock()
	{
	}
	bool Clock::Init()
	{
		return true;
	}
	//Counts fps
	void Clock::Update()
	{
		//How many frames passed
		static uint64_t frameCounter = 0;
		//How many seconds passed
		static double elapsedSeconds = 0.0;
		//Clock used to track time
		static std::chrono::high_resolution_clock clock;
		static auto t0 = clock.now();

		//Increment the number of frames
		++frameCounter;
		//Get the current time
		auto t1 = clock.now();
		//Calculate difference in time to get deltaTime
		auto deltaTime = t1 - t0;
		//Old time is now the current time
		t0 = t1;

		elapsedSeconds += deltaTime.count() * 1e-9;

		//When it reaches 1 second or greaterish
		if (elapsedSeconds > 1.0f) {
			char buffer[500];
			//How many frames during second
			auto fps = frameCounter / elapsedSeconds;
			//Print the time
			sprintf_s(buffer, 500, "FPS: %f\n", fps);
			printf("%s", buffer);

			frameCounter = 0;
			elapsedSeconds - 0.0;
		}
	}
	void Clock::Render()
	{
	}
	bool Clock::Shutdown()
	{
		return true;
	}
}