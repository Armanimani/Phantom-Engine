#include <iostream>

#include <core/logger/Logger.hpp>
#include <core/timer/Timer.hpp>

int main()
{
	phantom::core::Timer timer;
	std::cout << timer.time() << std::endl;
	phantom::core::Logger::instance().setLogToFile(true);
	phantom::core::Logger::instance().log_error("hi");
	std::cout << timer.time() << std::endl;
	std::cout << "Hello world" << std::endl;
}