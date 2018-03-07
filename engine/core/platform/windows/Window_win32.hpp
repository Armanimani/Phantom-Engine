#pragma once

#include "../../window/IWindow.hpp"

#include <Windows.h>
#include <map>

namespace phantom::core
{
	class Window_win32 : public IWindow
	{
	public:
		explicit Window_win32(std::unique_ptr<WindowSettings>& settings);

		void create() override;
		void update() const noexcept override;
		void clear() const noexcept override;
		void close() noexcept override;

		bool isClosed() const noexcept override;

		void focus() const noexcept override;
		void show() const noexcept override;
		void hide() const noexcept override;

		bool isFocused() const noexcept override;
		bool isVisible() const noexcept override;

		void maximize() const noexcept override;
		void minimize() const noexcept override;
		void restore() const noexcept override;
		void fullscreen(bool state = true) const noexcept override;

		bool isMinimized() const noexcept override;
		bool isMaximized() const noexcept override;
		bool isFullscreen() const noexcept override;

		void resizable(bool state = true) const noexcept override;
		void borderless(bool state = true) const noexcept override;

		bool isResizable() const noexcept override;
		bool isBorderless() const noexcept override;

		vec2ui mousePosition() const noexcept override;
		void setMousePosition(const vec2ui& position) const noexcept override;

		void clipMouse(const vec2ui& topLeft, const vec2ui& bottomRight) const noexcept override;
		std::array<vec2ui, 2> mouseClipArea() const noexcept override;

		void showMouse(bool state = true) const noexcept override;
		bool isMouseVisible() const noexcept override;

		vec2ui clientSize() const noexcept override;
		vec2ui position() const noexcept override;
		vec2ui size() const noexcept override;

		void setPosition(const vec2ui& position) const noexcept override;
		void setSize(const vec2ui& size) const noexcept override;

		std::string title() const noexcept override;
		void setTitle(const std::string& title) const noexcept override;

		void setIcon(const std::string& path) noexcept override;

	private:
		static const std::string WINDOW_CLASS_NAME;
		static bool s_registered_;
		static HINSTANCE s_hInstance_;
		static std::map<HWND, Window_win32*> s_handles_;

		static Window_win32* s_getWindow_(const HWND& hwnd);
		static void s_getModuleHandle_();
		static void s_registerWindowclass_();
		static LRESULT CALLBACK windowProc_callback_(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
		static void s_processInputEvent_(InputEvent* e, Window_win32* window);

		HWND hWnd_ {};
		HANDLE hIcon_ {};

	};
}