#pragma once

#include "ApplicationSettings.hpp"
#include "../window/Window.hpp"

namespace phantom::core
{
	struct Settings
	{
		Settings()
		{
			application = std::make_unique<ApplicationSettings>();
			window = std::make_unique<WindowSettings>();
		}
		
		std::unique_ptr<ApplicationSettings> application {};
		std::unique_ptr<WindowSettings> window {};
	};
}