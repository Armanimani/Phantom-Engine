#pragma once

#ifdef _WIN32
#include "../platform/windows/Window_win32.hpp"
namespace phantom::core
{
	using Window = Window_win32;
}
#endif
