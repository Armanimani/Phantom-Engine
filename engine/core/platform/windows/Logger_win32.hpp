#pragma once

#include <memory>
#include <windows.h>

#include "../../logger/ILogger.hpp"

namespace phantom::core
{
	class Logger_win32 : public ILogger
	{
	public:
		static Logger_win32& instance();

	private:
		enum class LogLevelColor : uint8
		{
			ERROR_COLOR = 12,
			WARNING_COLOR = 14,
			INFORMATION_COLOR = 10,
			MESSAGE_COLOR = 7,
			STATUS_COLOR = 11,
		};

		Logger_win32();
		
		HANDLE handle_;

		std::string getTime_() noexcept override;

		void console_preLog_(LogLevel level) noexcept override;
		void console_postLog_(LogLevel level) noexcept override;

		void file_preLog_(LogLevel level) noexcept override {}
		void file_postLog_(LogLevel level) noexcept override {}
	};
}