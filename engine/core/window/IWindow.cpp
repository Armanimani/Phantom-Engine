#include "IWindow.hpp"

namespace phantom::core
{
	IWindow::IWindow(std::unique_ptr<WindowSettings>& settings) : settings_(std::move(settings))
	{

	}
}