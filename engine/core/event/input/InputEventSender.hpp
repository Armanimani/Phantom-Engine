#pragma once

#include "../events.hpp"
#include "../../event/input/KeyboardEvent.hpp"
#include "../../event/input/MouseEvent.hpp"

namespace phantom::core
{
	class InputEventSender
	{
	public:
		Signal<Slot<void(const KeyboardEvent&)>> signal_keyboardButtonDown;
		Signal<Slot<void(const KeyboardEvent&)>> signal_keyboardButtonUp;
		Signal<Slot<void(const MouseEvent&)>> signal_mouseButtonDown;
		Signal<Slot<void(const MouseEvent&)>> signal_mouseButtonUp;
		Signal<Slot<void(const MouseEvent&)>> signal_mouseDoubleClick;
		Signal<Slot<void(const MouseEvent&)>> signal_mouseWheel;
		Signal<Slot<void(const MouseEvent&)>> signal_mouseMove;
	};
}