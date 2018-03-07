#pragma once

#ifdef _WIN32
#include"../platform/windows/System_win32.hpp"
namespace phantom::core
{
	using System = System_win32;
}
#endif