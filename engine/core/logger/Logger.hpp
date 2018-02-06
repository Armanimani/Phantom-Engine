#pragma once


	#ifdef _WIN32
	#include"../platform/windows/Logger_win32.hpp"
	namespace phantom::core
	{
		using Logger = Logger_win32;
	}
	#endif