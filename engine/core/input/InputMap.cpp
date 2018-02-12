#include "InputMap.hpp"

namespace phantom::core
{
	void InputMap::replaceContext(InputMap context) noexcept
	{
		keyboardDown_ = std::move(context.keyboardDown_);
		keyboardUp_ = std::move(context.keyboardDown_);

		mouseDown_ = std::move(context.mouseDown_);
		mouseUp_ = std::move(context.mouseUp_);
		mouseDoubleClick_ = std::move(context.mouseDoubleClick_);

		mouseWheel_ = std::move(mouseWheel_);
		mouseMove_ = std::move(mouseMove_);
	}

	void InputMap::link_keyboardDown(const KeyboardKey key, Slot<void(void)> slot)
	{
		keyboardDown_[key] = std::make_unique<Slot<void(void)>>(std::move(slot));
	}

	void InputMap::link_keyboardUp(const KeyboardKey key, Slot<void(void)> slot)
	{
		keyboardUp_[key] = std::make_unique<Slot<void(void)>>(std::move(slot));
	}

	void InputMap::link_mouseButtonDown(const MouseKey key, Slot<void(void)> slot)
	{
		mouseDown_[key] = std::make_unique<Slot<void(void)>>(std::move(slot));
	}

	void InputMap::link_mouseButtonUp(const MouseKey key, Slot<void(void)> slot)
	{
		mouseUp_[key] = std::make_unique<Slot<void(void)>>(std::move(slot));
	}

	void InputMap::link_mouseDoubleClick(const MouseKey key, Slot<void(void)> slot)
	{
		mouseDoubleClick_[key] = std::make_unique<Slot<void(void)>>(std::move(slot));
	}

	void InputMap::link_mouseWheel(Slot<void(const uint)> slot)
	{
		mouseWheel_ = std::make_unique<Slot<void(const uint)>>(std::move(slot));
	}

	void InputMap::link_mouseMove(Slot<void(const vec2ui)> slot)
	{
		mouseMove_ = std::make_unique<Slot<void(const vec2ui)>>(std::move(slot));
	}

	void InputMap::unlink_keyboardDown(const KeyboardKey key)
	{
		keyboardDown_[key].release();
	}

	void InputMap::unlink_keyboardUp(const KeyboardKey key)
	{
		keyboardUp_[key].release();
	}

	void InputMap::unlink_mouseButtonDown(const MouseKey key)
	{
		mouseDown_[key].release();
	}

	void InputMap::unlink_mouseButtonUp(const MouseKey key)
	{
		mouseUp_[key].release();
	}

	void InputMap::unlink_mouseDoubleClick(const MouseKey key)
	{
		mouseDoubleClick_[key].release();
	}

	void InputMap::unlink_mouseWheel()
	{
		mouseWheel_.release();
	}

	void InputMap::unlink_mouseMove()
	{
		mouseMove_.release();
	}

	void InputMap::call_keyboardDown(const KeyboardKey key)
	{
		if (keyboardDown_[key])
		{
			(*keyboardDown_[key])();
		}
	}

	void InputMap::call_keyboardUp(const KeyboardKey key)
	{
		if (keyboardUp_[key])
		{
			(*keyboardUp_[key])();
		}
	}

	void InputMap::call_mouseButtonDown(const MouseKey key)
	{
		if (mouseDown_[key])
		{
			(*mouseDown_[key])();
		}
	}

	void InputMap::call_mouseButtonUp(const MouseKey key)
	{
		if (mouseUp_[key])
		{
			(*mouseUp_[key])();
		}
	}

	void InputMap::call_mouseDoubleClick(const MouseKey key)
	{
		if (mouseDoubleClick_[key])
		{
			(*mouseDoubleClick_[key])();
		}
	}

	void InputMap::call_mouseWheel(const uint value)
	{
		if (mouseWheel_)
		{
			(*mouseWheel_)(value);
		}
	}

	void InputMap::call_mouseMove(const vec2ui position)
	{
		if (mouseMove_)
		{
			(*mouseMove_)(position);
		}
	}
}