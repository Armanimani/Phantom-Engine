#pragma once

#include "../common.hpp"
#include "to_string.hpp"

#include <type_traits>
#include <string>
#include <mutex>
#include <fstream>

namespace phantom::core
{
	class ILogger
	{
	public:
		enum class LogLevel : uint8
		{
			ERROR_LEVEL = 1 << 0,
			WARNING_LEVEL = 1 << 1,
			INFROMATION_LEVEL = 1 << 2,
			STATUS_LEVEL = 1 << 3,
			MESSAGE_LEVEL = 1 << 4,
		};

		void setLevel(const LogLevel level) noexcept;
		void setLogToFile(const bool state = true);

		template<typename T>
		void log_error(T&& data) noexcept;

		template<typename T>
		void log_warning(T&& data) noexcept;

		template<typename T>
		void log_information(T&& data) noexcept;

		template<typename T>
		void log_status(T&& data) noexcept;

		template<typename T>
		void log_messsage(T&& data) noexcept;

	private:
		std::mutex m_log_;

		LogLevel level_ { static_cast<LogLevel>(0xFF)};
		bool logToFile_ { true };

		std::string to_string_(const LogLevel level);
		std::string get_stamp_(const LogLevel level);

		void log_(const std::string& data, const LogLevel level) noexcept;
		void console_log_(const std::string& message) noexcept;
		void file_log_(const std::string& message) noexcept;

	protected:
		ILogger() {}

		std::ofstream file_;

		virtual std::string getTime_() noexcept { return "NYI"; }

		virtual void console_preLog_(const LogLevel level) noexcept {}
		virtual void console_postLog_(const LogLevel level) noexcept {}

		virtual void file_preLog_(const LogLevel level) noexcept {}
		virtual void file_postLog_(const LogLevel level) noexcept {}
	};

	inline
	ILogger::LogLevel operator|(const ILogger::LogLevel l1, const ILogger::LogLevel l2)
	{
		using type_t = std::underlying_type<ILogger::LogLevel>::type;
		return static_cast<ILogger::LogLevel>(static_cast<type_t>(l1) | static_cast<type_t>(l2));
	}

	inline
	ILogger::LogLevel operator&(const ILogger::LogLevel l1, const ILogger::LogLevel l2)
	{
		using type_t = std::underlying_type<ILogger::LogLevel>::type;
		return static_cast<ILogger::LogLevel>(static_cast<type_t>(l1) & static_cast<type_t>(l2));
	}

	template<typename T>
	void ILogger::log_error(T&& data) noexcept
	{
		if (static_cast<bool>(level_ & LogLevel::ERROR_LEVEL))
		{
			auto message = get_stamp_(LogLevel::ERROR_LEVEL) + impl::to_string(data);
			log_(message, LogLevel::ERROR_LEVEL);
		}
	}

	template<typename T>
	void ILogger::log_warning(T&& data) noexcept
	{
		if (static_cast<bool>(level_ & LogLevel::WARNING_LEVEL))
		{
			auto message = get_stamp_(LogLevel::WARNING_LEVEL) + impl::to_string(data);
			log_(message, LogLevel::WARNING_LEVEL);
		}
	}

	template<typename T>
	void ILogger::log_information(T&& data) noexcept
	{
		if (static_cast<bool>(level_ & LogLevel::INFROMATION_LEVEL))
		{
			auto message = get_stamp_(LogLevel::INFROMATION_LEVEL) + impl::to_string(data);
			log_(message, LogLevel::INFROMATION_LEVEL);
		}
	}

	template<typename T>
	void ILogger::log_status(T&& data) noexcept
	{
		if (static_cast<bool>(level_ & LogLevel::STATUS_LEVEL))
		{
			auto message = get_stamp_(LogLevel::STATUS_LEVEL) + impl::to_string(data);
			log_(message, LogLevel::STATUS_LEVEL);
		}
	}

	template<typename T>
	void ILogger::log_messsage(T&& data) noexcept
	{
		if (static_cast<bool>(level_ & LogLevel::MESSAGE_LEVEL))
		{
			auto message = get_stamp_(LogLevel::MESSAGE_LEVEL) + impl::to_string(data);
			log_(message, LogLevel::MESSAGE_LEVEL);
		}
	}
}