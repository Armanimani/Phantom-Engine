#pragma once

#include "InputEvent.hpp"
#include "../../input/KeyboardKey.hpp"

namespace phantom::core
{
	struct KeyboardEvent : public InputEvent
	{
		KeyboardKey key = KeyboardKey::KEY_NO_CODE;
	};
}