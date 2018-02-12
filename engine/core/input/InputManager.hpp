#pragma once

#include "../event/events.hpp"
#include "../event/input/InputEventSender.hpp"
#include "../event/input/KeyboardEvent.hpp"
#include "../event/input/MouseEvent.hpp"
#include "MouseKey.hpp"
#include "KeyboardKey.hpp"
#include "InputMap.hpp"

#include <array>
#include <map>

namespace phantom::core
{
	constexpr int32 MAX_KEYS = 512;
	constexpr int32 MAX_MOUSE_KEYS = 10;

	class InputManager
	{
	public:
		InputManager();

		InputMap context;

		void event_connectToSender(InputEventSender* sender);
		void update() noexcept;
		void clear() noexcept;

		bool isKeyboardKeyDown(const KeyboardKey key) const noexcept;
		bool isKeyboatdKeyUp(const KeyboardKey key) const noexcept;
		bool isKeyboardKeyHeld(const KeyboardKey key) const noexcept;
		bool wasKeyboardKeyDown(const KeyboardKey key) const noexcept;
		bool wasKeyboardKeyUp(const KeyboardKey key) const noexcept;

		bool isMouseButtonDown(const MouseKey key) const noexcept;
		bool isMouseButtonUp(const MouseKey key) const noexcept;
		bool isMouseBottonHeld(const MouseKey key) const noexcept;
		bool wasMouseBottonDown(const MouseKey key) const noexcept;
		bool wasMouseBottonUp(const MouseKey key) const noexcept;

		vec2ui mousePosition() const noexcept;
		uint mouseWheel() const noexcept;

	private:
		InputEventSender* prevSender_ {};

		std::unique_ptr<Slot<void(const KeyboardEvent&)>> slot_keyboardButtonDown_;
		std::unique_ptr<Slot<void(const KeyboardEvent&)>> slot_keyboardButtonUp_;
		std::unique_ptr<Slot<void(const MouseEvent&)>> slot_mouseButtonDown_;
		std::unique_ptr<Slot<void(const MouseEvent&)>> slot_mouseButtonUp_;
		std::unique_ptr<Slot<void(const MouseEvent&)>> slot_mouseDoubleClick_;
		std::unique_ptr<Slot<void(const MouseEvent&)>> slot_mouseWheel_;
		std::unique_ptr<Slot<void(const MouseEvent&)>> slot_mouseMove_;

		void preprocessEvent_(const InputEvent* e) noexcept;

		void on_keyboardButtonDown(const KeyboardEvent& e) noexcept;
		void on_keyboardButtonUp(const KeyboardEvent& e) noexcept;
		void on_mouseButtonDown(const MouseEvent& e) noexcept;
		void on_mouseButtonUp(const MouseEvent& e) noexcept;
		void on_mouseDoubleClick(const MouseEvent& e) noexcept;
		void on_mouseWheel(const MouseEvent& e) noexcept;
		void on_mouseMove(const MouseEvent& e) noexcept;

		std::array<bool, MAX_KEYS> keyboardState_ {};
		std::array<bool, MAX_KEYS> prevKeyboardState_ {};

		std::array<bool, MAX_MOUSE_KEYS> mouseState_ {};
		std::array<bool, MAX_MOUSE_KEYS> prevMouseState_ {};

		vec2ui mousePosition_ {};
		uint mouseWheelValue_ {};
	};
}