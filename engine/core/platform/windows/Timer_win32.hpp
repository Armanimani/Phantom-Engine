#pragma once

#include "../../timer/ITimer.hpp"

#include <Windows.h>

namespace phantom::core
{
	class Timer_win32 : public ITimer
	{
	public:
		Timer_win32();

		void reset() noexcept override;
		float time() noexcept override;

	private:
		LARGE_INTEGER timeFrequency_ {};
		LARGE_INTEGER startingTime_ {};
	};
}