#pragma once

namespace phantom::core
{
	enum struct MouseKey
	{
		MOUSE_NO_CODE = 0x00,
		MOUSE_LEFT = 0x01,
		MOUSE_RIGHT = 0x02,
		MOUSE_MIDDLE = 0x03,
		MOUSE_WHEEL = 0x04,
		MOUSE_EXTRA1 = 0x05,
		MOUSE_EXTRA2 = 0x06,
	};

	inline MouseKey operator|(MouseKey lhs, MouseKey rhs)
	{
		return static_cast<MouseKey>(static_cast<uint>(lhs) | static_cast<uint>(rhs));
	}

	inline MouseKey operator&(MouseKey lhs, MouseKey rhs)
	{
		return static_cast<MouseKey>(static_cast<uint>(lhs) & static_cast<uint>(rhs));
	}

	inline MouseKey& operator|=(MouseKey& lhs, MouseKey rhs)
	{
		lhs = static_cast<MouseKey>(static_cast<uint>(lhs) | static_cast<uint>(rhs));
		return lhs;
	}

	inline MouseKey& operator&=(MouseKey& lhs, MouseKey rhs)
	{
		lhs = static_cast<MouseKey>(static_cast<uint>(lhs) & static_cast<uint>(rhs));
		return lhs;
	}

	inline bool toBool(const MouseKey code)
	{
		return !(code == MouseKey::MOUSE_NO_CODE);
	}
}