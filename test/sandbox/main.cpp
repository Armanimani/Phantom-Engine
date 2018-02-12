#include <core/application/Application.hpp>

int main()
{
	std::unique_ptr<phantom::core::Settings> settings = std::make_unique<phantom::core::Settings>();
	phantom::core::Application app(settings);
	app.start();
}