#pragma once

#include "../events.hpp"

namespace phantom::core
{
	class WindowEventSender
	{
	public:
		Signal<Slot<void(void)>> signal_create;
		Signal<Slot<void(void)>> signal_show;
		Signal<Slot<void(void)>> signal_hide;
		Signal<Slot<void(void)>> signal_focus;
		Signal<Slot<void(void)>> signal_unfocus;
		Signal<Slot<void(void)>> signal_paint;
		Signal<Slot<void(void)>> signal_close;
		Signal<Slot<void(void)>> signal_destroy;
		Signal<Slot<void(const vec2ui&)>> signal_move;
		Signal<Slot<void(const vec2ui&)>> signal_resize;
	};
}