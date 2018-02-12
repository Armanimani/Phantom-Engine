#pragma once

#include "../common.hpp"

#include <string>

namespace phantom::core
{
	struct WindowSettings
	{
		vec2ui size { 800, 600 };
		bool fullscreen { false };
		std::string title { "Phantom-Engine" };
	};
}