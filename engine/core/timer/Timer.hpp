#pragma once

#include "TimeStep.hpp"

#ifdef _WIN32
#include "../platform/windows/Timer_win32.hpp"
namespace phantom::core
{
	using Timer = Timer_win32;
}
#endif
