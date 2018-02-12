#pragma once

#include "../common.hpp"

#include <string>

namespace phantom::core::impl
{
	template<typename T>
	std::string to_string(T&& data)
	{
		return std::string("Logging ").append(typeid(data).name()).append(" is not implemented yet!");
	}

	template<std::size_t N>
	std::string to_string(const char(&data)[N])
	{
		return { data };
	}

	template<>
	inline std::string to_string<std::string>(std::string&& data)
	{
		return { data };
	}

	template<>
	inline std::string to_string<decltype(((std::string*)nullptr)->c_str())&> (decltype(((std::string*)nullptr)->c_str())& data)
	{
		return { data };
	}

	template<>
	inline std::string to_string<float&>(float& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const float&>(const float& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<double&>(double& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const double&>(const double& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<int8&>(int8& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const int8&>(const int8& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<int16&>(int16& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const int16&>(const int16& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<int32&>(int32& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const int32&>(const int32& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<int64&>(int64& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const int64&>(const int64& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<uint8&>(uint8& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const uint8&>(const uint8& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<uint16&>(uint16& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const uint16&>(const uint16& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<uint32&>(uint32& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const uint32&>(const uint32& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<uint64&>(uint64& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<const uint64&>(const uint64& data)
	{
		return std::to_string(data);
	}

	template<>
	inline std::string to_string<vec2&>(vec2& data)
	{
		return { "{" + std::to_string(data.x) + ", " + std::to_string(data.y) + "}" };
	}

	template<>
	inline std::string to_string<const vec2&>(const vec2& data)
	{
		return { "{" + std::to_string(data.x) + ", " + std::to_string(data.y) + "}" };
	}

	template<>
	inline std::string to_string<vec2i&>(vec2i& data)
	{
		return { "{" + std::to_string(data.x) + ", " + std::to_string(data.y) + "}" };
	}

	template<>
	inline std::string to_string<const vec2i&>(const vec2i& data)
	{
		return { "{" + std::to_string(data.x) + ", " + std::to_string(data.y) + "}" };
	}

	template<>
	inline std::string to_string<vec2ui&>(vec2ui& data)
	{
		return { "{" + std::to_string(data.x) + ", " + std::to_string(data.y) + "}" };
	}

	template<>
	inline std::string to_string<const vec2ui&>(const vec2ui& data)
	{
		return { "{" + std::to_string(data.x) + ", " + std::to_string(data.y) + "}" };
	}

	template<>
	inline std::string to_string<vec2us&>(vec2us& data)
	{
		return { "{" + std::to_string(data.x) + ", " + std::to_string(data.y) + "}" };
	}

	template<>
	inline std::string to_string<const vec2us&>(const vec2us& data)
	{
		return { "{" + std::to_string(data.x) + ", " + std::to_string(data.y) + "}" };
	}

}