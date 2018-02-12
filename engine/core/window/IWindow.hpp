#pragma once

#include "../common.hpp"
#include "WindowSettings.hpp"
#include "../event/window/WindowEventSender.hpp"
#include "../event/input/InputEventSender.hpp"

#include <string>
#include <memory>
#include <array>

namespace phantom::core
{
	class IWindow : public WindowEventSender, public InputEventSender
	{
	public:
		IWindow(std::unique_ptr<WindowSettings>& settings);
		virtual ~IWindow() {}

		IWindow(IWindow&& rhs) = delete;
		IWindow(IWindow& rhs) = delete;
		IWindow& operator=(IWindow& rhs) noexcept = delete;
		IWindow& operator=(IWindow&& rhs) noexcept = delete;

		virtual void create() = 0;
		virtual void update() const noexcept = 0;
		virtual void clear() const noexcept = 0;
		virtual void close() noexcept = 0;

		virtual bool isClosed() const noexcept = 0;

		virtual void focus() const noexcept = 0;
		virtual void show() const noexcept = 0;
		virtual void hide() const noexcept = 0;

		virtual bool isFocused() const noexcept = 0;
		virtual bool isVisible() const noexcept = 0;

		virtual void maximize() const noexcept = 0;
		virtual void minimize() const noexcept = 0;
		virtual void restore() const noexcept = 0;
		virtual void fullscreen(const bool state = true) const noexcept = 0;

		virtual bool isMaximized() const noexcept = 0;
		virtual bool isMinimized() const noexcept = 0;
		virtual bool isFullscreen() const noexcept = 0;

		virtual void resizable(const bool state = true) const noexcept = 0;
		virtual void borderless(const bool state = true) const noexcept = 0;

		virtual bool isResizable() const noexcept = 0;
		virtual bool isBorderless() const noexcept = 0;

		virtual vec2ui mousePosition() const noexcept = 0;
		virtual void setMousePosition(const vec2ui& position) const noexcept = 0;

		virtual void clipMouse(const vec2ui& topRitopLeftght, const vec2ui& bottomRight) const noexcept = 0;
		virtual std::array<vec2ui, 2> mouseClipArea() const noexcept = 0;

		virtual void showMouse(const bool state = true) const noexcept = 0;
		virtual bool isMouseVisible() const noexcept = 0;

		virtual vec2ui clientSize() const noexcept = 0;
		virtual vec2ui position() const noexcept = 0;
		virtual vec2ui size() const noexcept = 0;

		virtual void setPosition(const vec2ui& position) const noexcept = 0;
		virtual void setSize(const vec2ui& size) const noexcept = 0;

		virtual std::string title() const noexcept = 0;
		virtual void setTitle(const std::string& title) const noexcept = 0;

		virtual void setIcon(const std::string& path) noexcept = 0;

	protected:
		std::unique_ptr<WindowSettings> settings_ { nullptr };
	};
}