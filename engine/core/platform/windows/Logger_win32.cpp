#include "Logger_win32.hpp"

namespace phantom::core
{
	Logger_win32& Logger_win32::instance()
	{
		static Logger_win32 instance;
		return instance;
	}


	Logger_win32::Logger_win32()
	{
		handle_ = GetStdHandle(STD_OUTPUT_HANDLE);
	}

	std::string Logger_win32::getTime_() noexcept
	{
		SYSTEMTIME time;
		GetSystemTime(&time);
		return { std::to_string(time.wYear) + '/' + std::to_string(time.wMonth) + '/' + std::to_string(time.wDay) + ' '  + std::to_string(time.wHour) + ':' + std::to_string(time.wMinute) + ':' + std::to_string(time.wSecond) };
	}

	void Logger_win32::console_preLog_(const LogLevel level) noexcept
	{
		auto color = [&level] () 
		{
			switch (level)
			{
				default:
				{
					return LogLevelColor::MESSAGE_COLOR;
				}
				case (LogLevel::ERROR_LEVEL):
				{
					return LogLevelColor::ERROR_COLOR;
				}
				case (LogLevel::WARNING_LEVEL):
				{
					return LogLevelColor::WARNING_COLOR;
				}
				case (LogLevel::INFROMATION_LEVEL):
				{
					return LogLevelColor::INFORMATION_COLOR;
				}
				case (LogLevel::STATUS_LEVEL):
				{
					return LogLevelColor::STATUS_COLOR;
				}
				case (LogLevel::MESSAGE_LEVEL):
				{
					return LogLevelColor::MESSAGE_COLOR;
				}
			}
		}();

		SetConsoleTextAttribute(handle_, static_cast<WORD>(color));
	}

	void Logger_win32::console_postLog_(const LogLevel level) noexcept
	{
		SetConsoleTextAttribute(handle_, static_cast<WORD>(LogLevelColor::MESSAGE_COLOR));
	}
}