#include "WindowEventListener.hpp"

namespace phantom::core
{
	WindowEventListener::WindowEventListener()
	{
		slot_create_ = std::make_unique<Slot<void(void)>>(this, &WindowEventListener::on_windowCreate);
		slot_show_ = std::make_unique<Slot<void(void)>>(this, &WindowEventListener::on_windowShow);
		slot_hide_ = std::make_unique<Slot<void(void)>>(this, &WindowEventListener::on_windowHide);
		slot_focus_ = std::make_unique<Slot<void(void)>>(this, &WindowEventListener::on_windowFocus);
		slot_unfocus_ = std::make_unique<Slot<void(void)>>(this, &WindowEventListener::on_windowUnfocus);
		slot_paint_ = std::make_unique<Slot<void(void)>>(this, &WindowEventListener::on_windowPaint);
		slot_close_ = std::make_unique<Slot<void(void)>>(this, &WindowEventListener::on_windowClose);
		slot_destroy_ = std::make_unique<Slot<void(void)>>(this, &WindowEventListener::on_windowDestroy);
		slot_move_ = std::make_unique<Slot<void(const vec2ui&)>>(this, &WindowEventListener::on_windowMove);
		slot_resize_ = std::make_unique<Slot<void(const vec2ui&)>>(this, &WindowEventListener::on_windowResize);
	}

	void WindowEventListener::event_connectToSender(WindowEventSender* sender)
	{
		if (prevSender_)
		{
			prevSender_->signal_create.disconnect(*slot_create_);
			prevSender_->signal_show.disconnect(*slot_show_);
			prevSender_->signal_hide.disconnect(*slot_hide_);
			prevSender_->signal_focus.disconnect(*slot_focus_);
			prevSender_->signal_unfocus.disconnect(*slot_unfocus_);
			prevSender_->signal_paint.disconnect(*slot_paint_);
			prevSender_->signal_close.disconnect(*slot_close_);
			prevSender_->signal_close.disconnect(*slot_destroy_);
			prevSender_->signal_move.disconnect(*slot_move_);
			prevSender_->signal_resize.disconnect(*slot_resize_);
		}
		prevSender_ = sender;

		sender->signal_create.connect(*slot_create_);
		sender->signal_show.connect(*slot_show_);
		sender->signal_hide.connect(*slot_hide_);
		sender->signal_focus.connect(*slot_focus_);
		sender->signal_unfocus.connect(*slot_unfocus_);
		sender->signal_paint.connect(*slot_paint_);
		sender->signal_close.connect(*slot_close_);
		sender->signal_close.connect(*slot_destroy_);
		sender->signal_move.connect(*slot_move_);
		sender->signal_resize.connect(*slot_resize_);
	}
}