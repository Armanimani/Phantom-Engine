#pragma once

#include <string>

namespace phantom::core::impl
{
	template<typename T>
	std::string to_string(T&& data)
	{
		return std::string("Logging ").append(typeid(data).name()).append(" is not implemented yet!");
	}
}