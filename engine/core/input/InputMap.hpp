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
		InputMap& operator=(const InputMap&) = delete;
		InputMap& operator=(const InputMap&&) = delete;

		void replaceContext(InputMap context) noexcept;

		void link_keyboardDown(const KeyboardKey key, Slot<void(void)> slot);
		void link_keyboardUp(const KeyboardKey key, Slot<void(void)> slot);
		void link_mouseButtonDown(const MouseKey key, Slot<void(void)> slot);
		void link_mouseButtonUp(const MouseKey key, Slot<void(void)> slot);
		void link_mouseDoubleClick(const MouseKey key, Slot<void(void)> slot);
		void link_mouseWheel(Slot<void(const uint)> slot);
		void link_mouseMove(Slot<void(const vec2ui)> slot);

		void unlink_keyboardDown(const KeyboardKey key);
		void unlink_keyboardUp(const KeyboardKey key);
		void unlink_mouseButtonDown(const MouseKey key);
		void unlink_mouseButtonUp(const MouseKey key);
		void unlink_mouseDoubleClick(const MouseKey key);
		void unlink_mouseWheel();
		void unlink_mouseMove();

		void call_keyboardDown(const KeyboardKey key);
		void call_keyboardUp(const KeyboardKey key);
		void call_mouseButtonDown(const MouseKey key);
		void call_mouseButtonUp(const MouseKey key);
		void call_mouseDoubleClick(const MouseKey key);
		void call_mouseWheel(const uint value);
		void call_mouseMove(const vec2ui position);

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