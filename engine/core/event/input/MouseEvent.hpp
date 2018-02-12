#pragma once

#include "InputEvent.hpp"
#include "../../input/MouseKey.hpp"

namespace phantom::core
{
	struct MouseEvent : public InputEvent
	{
		MouseKey key { MouseKey::MOUSE_NO_CODE };
		int wheel { 0 };	
	};
}