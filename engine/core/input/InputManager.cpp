#include "InputManager.hpp"

namespace phantom::core
{
	InputManager::InputManager()
	{
		slot_keyboardButtonDown_ = std::make_unique<Slot<void(const KeyboardEvent&)>>(this, &InputManager::on_keyboardButtonDown);
		slot_keyboardButtonUp_ = std::make_unique<Slot<void(const KeyboardEvent&)>>(this, &InputManager::on_keyboardButtonUp);
		slot_mouseButtonDown_ = std::make_unique<Slot<void(const MouseEvent&)>>(this, &InputManager::on_mouseButtonDown);
		slot_mouseButtonUp_ = std::make_unique<Slot<void(const MouseEvent&)>>(this, &InputManager::on_mouseButtonUp);
		slot_mouseDoubleClick_ = std::make_unique<Slot<void(const MouseEvent&)>>(this, &InputManager::on_mouseDoubleClick);
		slot_mouseWheel_ = std::make_unique<Slot<void(const MouseEvent&)>>(this, &InputManager::on_mouseWheel);
		slot_mouseMove_ = std::make_unique<Slot<void(const MouseEvent&)>>(this, &InputManager::on_mouseMove);

		clear();
	}

	void InputManager::event_connectToSender(InputEventSender* sender)
	{
		if (prevSender_)
		{
			prevSender_->signal_keyboardButtonDown.disconnect(*slot_keyboardButtonDown_);
			prevSender_->signal_keyboardButtonUp.disconnect(*slot_keyboardButtonUp_);
			prevSender_->signal_mouseButtonDown.disconnect(*slot_mouseButtonDown_);
			prevSender_->signal_mouseButtonUp.disconnect(*slot_mouseButtonUp_);
			prevSender_->signal_mouseDoubleClick.disconnect(*slot_mouseDoubleClick_);
			prevSender_->signal_mouseWheel.disconnect(*slot_mouseWheel_);
			prevSender_->signal_mouseMove.disconnect(*slot_mouseMove_);
		}

		prevSender_ = sender;

		sender->signal_keyboardButtonDown.connect(*slot_keyboardButtonDown_);
		sender->signal_keyboardButtonUp.connect(*slot_keyboardButtonUp_);
		sender->signal_mouseButtonDown.connect(*slot_mouseButtonDown_);
		sender->signal_mouseButtonUp.connect(*slot_mouseButtonUp_);
		sender->signal_mouseDoubleClick.connect(*slot_mouseDoubleClick_);
		sender->signal_mouseWheel.connect(*slot_mouseWheel_);
		sender->signal_mouseMove.connect(*slot_mouseMove_);
	}

	void InputManager::update() noexcept
	{
		prevKeyboardState_ = keyboardState_;
		prevMouseState_ = mouseState_;
	}

	void InputManager::clear() noexcept
	{
		keyboardState_.fill(false);
		prevKeyboardState_.fill(false);
		mouseState_.fill(false);
		prevMouseState_.fill(false);
	}

	bool InputManager::isKeyboardKeyDown(const KeyboardKey key) const noexcept
	{
		return (keyboardState_[static_cast<uint>(key)]) ? true : false;
	}

	bool InputManager::isKeyboatdKeyUp(const KeyboardKey key) const noexcept
	{
		return (keyboardState_[static_cast<uint>(key)]) ? false : true;
	}

	bool InputManager::isKeyboardKeyHeld(const KeyboardKey key) const noexcept
	{
		return (keyboardState_[static_cast<uint>(key)] && prevKeyboardState_[static_cast<uint>(key)]) ? true : false;
	}

	bool InputManager::wasKeyboardKeyDown(const KeyboardKey key) const noexcept
	{
		return (prevKeyboardState_[static_cast<uint>(key)]) ? true : false;
	}

	bool InputManager::wasKeyboardKeyUp(const KeyboardKey key) const noexcept
	{
		return (prevKeyboardState_[static_cast<uint>(key)]) ? false : true;
	}

	bool InputManager::isMouseButtonDown(const MouseKey key) const noexcept
	{
		return (mouseState_[static_cast<uint>(key)]) ? true : false;
	}

	bool InputManager::isMouseButtonUp(const MouseKey key) const noexcept
	{
		return (mouseState_[static_cast<uint>(key)]) ? false : true;
	}

	bool InputManager::isMouseBottonHeld(const MouseKey key) const noexcept
	{
		return (mouseState_[static_cast<uint>(key)] && prevMouseState_[static_cast<uint>(key)]) ? true : false;
	}

	bool InputManager::wasMouseBottonDown(const MouseKey key) const noexcept
	{
		return (prevMouseState_[static_cast<uint>(key)]) ? true : false;
	}

	bool InputManager::wasMouseBottonUp(const MouseKey key) const noexcept
	{
		return (prevMouseState_[static_cast<uint>(key)]) ? false : true;
	}

	phantom::core::vec2ui InputManager::mousePosition() const noexcept
	{
		return mousePosition_;
	}

	phantom::core::uint InputManager::mouseWheel() const noexcept
	{
		return mouseWheelValue_;
	}

	void InputManager::preprocessEvent_(const InputEvent* e) noexcept
	{
		mousePosition_ = e->position;

		keyboardState_[static_cast<uint>(KeyboardKey::KEY_ALT)] = e->alt;
		keyboardState_[static_cast<uint>(KeyboardKey::KEY_CTRL)] = e->ctrl;
		keyboardState_[static_cast<uint>(KeyboardKey::KEY_SHIFT)] = e->shift;
		keyboardState_[static_cast<uint>(KeyboardKey::KEY_WIN)] = e->windows;
	}

	void InputManager::on_keyboardButtonDown(const KeyboardEvent& e) noexcept
	{
		preprocessEvent_(&e);
		keyboardState_[static_cast<uint>(e.key)] = true;
		context.call_keyboardDown(e.key);
	}

	void InputManager::on_keyboardButtonUp(const KeyboardEvent& e) noexcept
	{
		preprocessEvent_(&e);
		keyboardState_[static_cast<uint>(e.key)] = false;
		context.call_keyboardUp(e.key);
	}

	void InputManager::on_mouseButtonDown(const MouseEvent& e) noexcept
	{
		preprocessEvent_(&e);
		mouseState_[static_cast<uint>(e.key)] = true;
		context.call_mouseButtonDown(e.key);
	}

	void InputManager::on_mouseButtonUp(const MouseEvent& e) noexcept
	{
		preprocessEvent_(&e);
		mouseState_[static_cast<uint>(e.key)] = false;
		context.call_mouseButtonUp(e.key);
	}

	void InputManager::on_mouseDoubleClick(const MouseEvent& e) noexcept
	{
		preprocessEvent_(&e);
		context.call_mouseDoubleClick(e.key);
	}

	void InputManager::on_mouseWheel(const MouseEvent& e) noexcept
	{
		preprocessEvent_(&e);
		mouseWheelValue_ = e.wheel;
		context.call_mouseWheel(e.wheel);
	}

	void InputManager::on_mouseMove(const MouseEvent& e) noexcept
	{
		preprocessEvent_(&e);
		context.call_mouseMove(e.position);
	}
}