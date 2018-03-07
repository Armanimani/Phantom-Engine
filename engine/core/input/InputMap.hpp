#pragma once

#include "KeyboardKey.hpp"
#include "MouseKey.hpp"
#include "../event/events.hpp"

#include <map>
#include <memory.h>


namespace phantom::core
{
	class InputMap
	{
	public:
		InputMap() = default;
		InputMap(const InputMap&) = delete;
		InputMap(const InputMap&&) = delete;
		~InputMap() = default;
		InputMap& operator=(const InputMap&) = delete;
		InputMap& operator=(const InputMap&&) = delete;

		void replaceContext(InputMap context) noexcept;

		void link_keyboardDown(KeyboardKey key, Slot<void(void)> slot);
		void link_keyboardUp(KeyboardKey key, Slot<void(void)> slot);
		void link_mouseButtonDown(MouseKey key, Slot<void(void)> slot);
		void link_mouseButtonUp(MouseKey key, Slot<void(void)> slot);
		void link_mouseDoubleClick(MouseKey key, Slot<void(void)> slot);
		void link_mouseWheel(Slot<void(const uint)> slot);
		void link_mouseMove(Slot<void(const vec2ui)> slot);

		void unlink_keyboardDown(KeyboardKey key);
		void unlink_keyboardUp(KeyboardKey key);
		void unlink_mouseButtonDown(MouseKey key);
		void unlink_mouseButtonUp(MouseKey key);
		void unlink_mouseDoubleClick(MouseKey key);
		void unlink_mouseWheel();
		void unlink_mouseMove();

		void call_keyboardDown(KeyboardKey key);
		void call_keyboardUp(KeyboardKey key);
		void call_mouseButtonDown(MouseKey key);
		void call_mouseButtonUp(MouseKey key);
		void call_mouseDoubleClick(MouseKey key);
		void call_mouseWheel(uint value);
		void call_mouseMove(vec2ui position);

	private:
		std::map<const KeyboardKey, std::unique_ptr<Slot<void(void)>>> keyboardDown_;
		std::map<const KeyboardKey, std::unique_ptr<Slot<void(void)>>> keyboardUp_;
		std::map<const MouseKey, std::unique_ptr<Slot<void(void)>>> mouseDown_;
		std::map<const MouseKey, std::unique_ptr<Slot<void(void)>>> mouseUp_;
		std::map<const MouseKey, std::unique_ptr<Slot<void(void)>>> mouseDoubleClick_;

		std::unique_ptr<Slot<void(const uint)>> mouseWheel_;
		std::unique_ptr<Slot<void(const vec2ui)>> mouseMove_;
	};
}