#pragma once

#include "../common.hpp"

namespace phantom::core
{
	enum class KeyboardKey : int32
	{
		KEY_NO_CODE = 0x00,

		KEY_A = 0x01,
		KEY_B = 0x02,
		KEY_C = 0x03,
		KEY_D = 0x04,
		KEY_E = 0x05,
		KEY_F = 0x06,
		KEY_G = 0x07,
		KEY_H = 0x08,
		KEY_I = 0x09,
		KEY_J = 0x0A,
		KEY_K = 0x0B,
		KEY_L = 0x0C,
		KEY_M = 0x0D,
		KEY_N = 0x0E,
		KEY_O = 0x0F,
		KEY_P = 0x10,
		KEY_Q = 0x11,
		KEY_R = 0x12,
		KEY_S = 0x13,
		KEY_T = 0x14,
		KEY_U = 0x15,
		KEY_V = 0x16,
		KEY_W = 0x17,
		KEY_X = 0x18,
		KEY_Y = 0x19,
		KEY_Z = 0x1A,

		KEY_0 = 0x1B,
		KEY_1 = 0x1C,
		KEY_2 = 0x1D,
		KEY_3 = 0x1E,
		KEY_4 = 0x1F,
		KEY_5 = 0x20,
		KEY_6 = 0x21,
		KEY_7 = 0x22,
		KEY_8 = 0x23,
		KEY_9 = 0x24,

		KEY_F1 = 0x25,
		KEY_F2 = 0x26,
		KEY_F3 = 0x27,
		KEY_F4 = 0x28,
		KEY_F5 = 0x29,
		KEY_F6 = 0x2A,
		KEY_F7 = 0x2B,
		KEY_F8 = 0x2C,
		KEY_F9 = 0x2D,
		KEY_F10 = 0x2F,
		KEY_F11 = 0x30,
		KEY_F12 = 0x31,
		KEY_F13 = 0x32,
		KEY_F14 = 0x33,
		KEY_F15 = 0x34,
		KEY_F16 = 0x35,
		KEY_F17 = 0x36,
		KEY_F18 = 0x37,
		KEY_F19 = 0x38,
		KEY_F20 = 0x39,
		KEY_F21 = 0x3A,
		KEY_F22 = 0x3B,
		KEY_F23 = 0x3C,
		KEY_F24 = 0x3D,

		KEY_NUM0 = 0x3E,
		KEY_NUM1 = 0x3F,
		KEY_NUM2 = 0x40,
		KEY_NUM3 = 0x41,
		KEY_NUM4 = 0x42,
		KEY_NUM5 = 0x43,
		KEY_NUM6 = 0x44,
		KEY_NUM7 = 0x45,
		KEY_NUM8 = 0x46,
		KEY_NUM9 = 0x47,

		KEY_NUMMULTIPLY = 0x48,
		KEY_NUMDIVIDE = 0x49,
		KEY_NUMADD = 0x4A,
		KEY_NUMSUBTRACT = 0x4B,

		KEY_BACKSPACE = 0x4C,
		KEY_TAB = 0x4D,
		KEY_SPACE = 0x4E,
		KEY_ENTER = 0x4F,
		KEY_CLEAR = 0x50,
		KEY_PAUSE = 0x51,
		KEY_ESCAPE = 0x52,

		KEY_PAGEUP = 0x53,
		KEY_PAGEDOWN = 0x54,
		KEY_END = 0x55,
		KEY_HOME = 0x56,
		KEY_INSERT = 0x57,
		KEY_DELETE = 0x58,
		KEY_MULTIPLY = 0x59,
		KEY_DIVIDE = 0x5A,
		KEY_ADD = 0x5B,
		KEY_SUBTRACT = 0x5C,
		KEY_SEPARATOR = 0x5D,
		KEY_DECIMAL = 0x5E,

		KEY_UP = 0x5F,
		KEY_DOWN = 0x60,
		KEY_LEFT = 0x61,
		KEY_RIGHT = 0x62,

		KEY_SELECT = 0x63,
		KEY_PRINTSCREEN = 0x64,
		KEY_SNAPSHOT = 0x65,
		KEY_EXE = 0x66,
		KEY_HELP = 0x67,
		KEY_SLEEP = 0x68,

		KEY_SCROLLLOCK = 0x69,
		KEY_CAPSLOCK = 0x6A,

		KEY_OEM_NUMEQUAL = 0x6B,
		KEY_OEM_DICTIONARY = 0x6C,
		KEY_OEM_UNREGISTER = 0x6D,
		KEY_OEM_REGISTER = 0x6E,
		KEY_OEM_LOYAYUBI = 0x6F,
		KEY_OEM_ROYAYUBI = 0x70,
		KEY_OEM_PLUS = 0x71,
		KEY_OEM_COMMA = 0x72,
		KEY_OEM_MINUS = 0x73,
		KEY_OEM_PERIOD = 0x74,
		KEY_OEM1 = 0x75,
		KEY_OEM2 = 0x76,
		KEY_OEM3 = 0x77,
		KEY_OEM4 = 0x78,
		KEY_OEM5 = 0x79,
		KEY_OEM6 = 0x7A,
		KEY_OEM7 = 0x7B,
		KEY_OEM8 = 0x7C,
		KEY_OEM_AX = 0x7D,
		KEY_OEM102 = 0x7E,

		KEY_BROWSER_BACK = 0x7F,
		KEY_BROWSER_FORWARD = 0x80,
		KEY_BROWSER_REFRESH = 0x81,
		KEY_BROWSER_STOP = 0x82,
		KEY_BROWSER_SEARCH = 0x83,
		KEY_BROWSER_FAVORITE = 0x84,
		KEY_BROWSER_HOME = 0x85,

		KEY_VOLUME_UP = 0x86,
		KEY_VOLUME_DOWN = 0x87,
		KEY_VOLUME_MUTE = 0x88,

		KEY_MEDIA_NEXT = 0x89,
		KEY_MEDIA_PREV = 0x8A,
		KEY_MEDIA_STOP = 0x8B,
		KEY_MEDIA_PLAY_PAUSE = 0x8C,
		KEY_MEDIA_SELECT = 0x8D,

		KEY_LAUNCH_APP1 = 0x8E,
		KEY_LAUNCH_APP2 = 0x8F,
		KEY_LAUNCH_MAIL = 0x90,

		KEY_APPLICATION = 0x91,

		KEY_RSHIFT = 0x92,
		KEY_RALT = 0x93,
		KEY_RCTRL = 0x94,
		KEY_RWIN = 0x95,
		KEY_LSHIFT = 0x96,
		KEY_LALT = 0x97,
		KEY_LCTRL = 0x98,
		KEY_LWIN = 0x99,

		KEY_SHIFT = 0x9A,
		KEY_ALT = 0x9B,
		KEY_CTRL = 0x9C,
		KEY_WIN = 0x9D,
	};

	inline KeyboardKey operator|(KeyboardKey lhs, KeyboardKey rhs)
	{
		return static_cast<KeyboardKey>(static_cast<uint>(lhs) | static_cast<uint>(rhs));
	}

	inline KeyboardKey operator&(KeyboardKey lhs, KeyboardKey rhs)
	{
		return static_cast<KeyboardKey>(static_cast<uint>(lhs) & static_cast<uint>(rhs));
	}

	inline KeyboardKey& operator|=(KeyboardKey& lhs, KeyboardKey rhs)
	{
		lhs = static_cast<KeyboardKey>(static_cast<uint>(lhs) | static_cast<uint>(rhs));
		return lhs;
	}

	inline KeyboardKey& operator&=(KeyboardKey& lhs, KeyboardKey rhs)
	{
		lhs = static_cast<KeyboardKey>(static_cast<uint>(lhs) & static_cast<uint>(rhs));
		return lhs;
	}

	inline bool toBool(const KeyboardKey code)
	{
		return !(code == KeyboardKey::KEY_NO_CODE);
	}
}