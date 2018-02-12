#pragma once

#include "../../event/events.hpp"
#include "WindowEventSender.hpp"

namespace phantom::core
{
	class WindowEventListener
	{
	public:
		WindowEventListener();

		void event_connectToSender(WindowEventSender* sender);

	protected:
		virtual void on_windowCreate() {};
		virtual void on_windowShow() {};
		virtual void on_windowHide() {};
		virtual void on_windowFocus() {};
		virtual void on_windowUnfocus() {};
		virtual void on_windowPaint() {};
		virtual void on_windowClose() {}
		virtual void on_windowDestroy() {}
		virtual void on_windowMove(const vec2ui& position) {};
		virtual void on_windowResize(const vec2ui& size) {};

	private:
		WindowEventSender* prevSender_ {};

		std::unique_ptr<Slot<void(void)>> slot_create_;
		std::unique_ptr<Slot<void(void)>> slot_show_;
		std::unique_ptr<Slot<void(void)>> slot_hide_;
		std::unique_ptr<Slot<void(void)>> slot_focus_;
		std::unique_ptr<Slot<void(void)>> slot_unfocus_;
		std::unique_ptr<Slot<void(void)>> slot_paint_;
		std::unique_ptr<Slot<void(void)>> slot_close_;
		std::unique_ptr<Slot<void(void)>> slot_destroy_;
		std::unique_ptr<Slot<void(const vec2ui&)>> slot_move_;
		std::unique_ptr<Slot<void(const vec2ui&)>> slot_resize_;
	};
}
