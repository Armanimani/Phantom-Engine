#include "Timer_win32.hpp"

namespace phantom::core
{
	Timer_win32::Timer_win32()
	{
		reset();
	}

	void Timer_win32::reset() noexcept
	{
		QueryPerformanceFrequency(&timeFrequency_);
		QueryPerformanceCounter(&startingTime_);
	}

	float Timer_win32::time() noexcept
	{
		LARGE_INTEGER newTime;
		QueryPerformanceCounter(&newTime);
		return static_cast<float>(newTime.QuadPart - startingTime_.QuadPart) / (timeFrequency_.QuadPart);
	}
}