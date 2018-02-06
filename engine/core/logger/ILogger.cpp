#include "ILogger.hpp"	

#include "../exceptions/Exception.hpp"
#include "../logger/Logger.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <sstream>

namespace phantom::core
{
	void ILogger::setLevel(const LogLevel level) noexcept
	{
		level_ = level;
	}

	void ILogger::setLogToFile(const bool state)
	{
		if (state)
		{
			logToFile_ = state;

			try
			{
				file_.open("../../logFile.log");
				if (!file_.good())
				{
					throw FileNotFoundException("Unable to open the engine log file.");
				}
			}
			catch (FileNotFoundException& e)
			{
				Logger::instance().log_warning(e.what());
				setLogToFile(false);
			}
		}
		else
		{
			logToFile_ = false;

			if (file_.is_open())
			{
				file_.close();
			}
		}
	}

	std::string ILogger::to_string_(const LogLevel level)
	{
		switch (level)
		{
			case (LogLevel::ERROR_LEVEL):
			{
				return "Error";
			}
			case (LogLevel::INFROMATION_LEVEL):
			{
				return "Information";
			}
			case (LogLevel::MESSAGE_LEVEL):
			{
				return "Message";
			}
			case (LogLevel::STATUS_LEVEL):
			{
				return "Status";
			}
			case (LogLevel::WARNING_LEVEL):
			{
				return "Warning";
			}
			default:
			{
				return "Unknown";
			}
		}
	}

	std::string ILogger::get_stamp_(const LogLevel level)
	{
		auto time = getTime_();

		std::stringstream id;
		id << std::this_thread::get_id();

		return { "[" + time + "] [thread" + id.str() + "] [" + to_string_(level) + "] : " };
	}

	void ILogger::log_(const std::string& data, const LogLevel level) noexcept
	{
		std::lock_guard<std::mutex> lock(m_log_);
		console_preLog_(level);
		console_log_(data);
		console_postLog_(level);

		if (logToFile_)
		{
			file_preLog_(level);
			file_log_(data);
			file_postLog_(level);
		}
	}

	void ILogger::console_log_(const std::string& message) noexcept
	{
		std::cout << message << std::endl;
	}

	void ILogger::file_log_(const std::string& message) noexcept
	{
		file_ << message << std::endl;
	}
}