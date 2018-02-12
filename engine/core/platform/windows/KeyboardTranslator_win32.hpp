#pragma once

#include "../../input/KeyboardKey.hpp"

#include <map>

namespace phantom::core
{
	class KeyboardTranslator_win32
	{
	public:
		static KeyboardKey translate(const uint key) noexcept;

	private:
		static std::map<const uint, KeyboardKey> database_;
	};
}