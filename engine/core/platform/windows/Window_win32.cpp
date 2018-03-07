#include "Window_win32.hpp"

#include "../../logger/Logger.hpp"
#include "../../exceptions/Exception.hpp"
#include "KeyboardTranslator_win32.hpp"

#include <windowsx.h>

namespace phantom::core
{
	const std::string Window_win32::WINDOW_CLASS_NAME = "Phantom_window";
	bool Window_win32::s_registered_ { false };
	HINSTANCE Window_win32::s_hInstance_ {};
	std::map<HWND, Window_win32*> Window_win32::s_handles_ {};

	Window_win32::Window_win32(std::unique_ptr<WindowSettings>& settings) : IWindow(settings)
	{
		s_getModuleHandle_();
		s_registerWindowclass_();
	}

	void Window_win32::create()
	{
		RECT rect {};
		rect.left = 0;
		rect.top = 0;
		rect.right = settings_->size.x;
		rect.bottom = settings_->size.y;

		DWORD dwStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_OVERLAPPEDWINDOW;
		DWORD dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		AdjustWindowRectEx(&rect, dwStyle, false, dwExStyle);

		int32 windowX = (GetSystemMetrics(SM_CXSCREEN) - settings_->size.x) / 2;
		int32 windowY = (GetSystemMetrics(SM_CYSCREEN) - settings_->size.y) / 2;
		hWnd_ = CreateWindowExA(dwExStyle, WINDOW_CLASS_NAME.c_str(), settings_->title.c_str(), dwStyle, windowX, windowY, rect.right - rect.left, rect.bottom - rect.top, nullptr, nullptr, s_hInstance_, nullptr);

		if (!hWnd_)
		{
			throw RuntimeException("Unable to create the window.");
		}
		s_handles_[hWnd_] = this;
	}

	void Window_win32::update() const noexcept
	{
		MSG msg {};
		while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	void Window_win32::clear() const noexcept
	{
		// NIY
		//Logger::instance().log_error("Window_win32::clear() is not implemented yet!");
	}

	void Window_win32::focus() const noexcept
	{
		if(isClosed())
		{
			Logger::instance().log_warning("Unable to focus the window, window is already closed");
		}
		else
		{
			SetFocus(hWnd_);
		}
	}

	void Window_win32::show() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to show the window, window is already closed");
		}
		else
		{
			ShowWindow(hWnd_, SW_SHOW);
			UpdateWindow(hWnd_);
		}
	}

	void Window_win32::hide() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to hide the window, window is already closed");
		}
		else
		{
			ShowWindow(hWnd_, SW_HIDE);
		}
	}
	
	void Window_win32::close() noexcept
	{
		CloseWindow(hWnd_);
		hWnd_ = nullptr;
	}

	bool Window_win32::isClosed() const noexcept
	{
		return (hWnd_ == nullptr);
	}

	bool Window_win32::isFocused() const noexcept
	{
		return (GetFocus() == hWnd_);
	}

	bool Window_win32::isVisible() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to retrieve the window visibility status, window is already closed");
			return false;
		}
		
		return IsWindowVisible(hWnd_);
	}

	void Window_win32::maximize() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to maximize the window, window is already closed");
		}
		else
		{
			ShowWindow(hWnd_, SW_MAXIMIZE);
		}
	}

	void Window_win32::minimize() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to minimize the window, window is already closed");
		}
		else
		{
			ShowWindow(hWnd_, SW_MINIMIZE);
		}
	}

	void Window_win32::restore() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to restore the window, window is already closed");
		}
		else
		{
			ShowWindow(hWnd_, SW_RESTORE);
		}
	}

	void Window_win32::fullscreen(const bool state) const noexcept
	{
		// NIY
		Logger::instance().log_error("Window_win32::fullscreen() is not implemented yet!");
	}

	bool Window_win32::isMinimized() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to check the windows minimize status, window is already closed");
			return false;
		}

		return IsIconic(hWnd_);
	}

	bool Window_win32::isMaximized() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to check the windows maximized status, window is already closed");
			return false;
		}

		return IsZoomed(hWnd_);
	}

	bool Window_win32::isFullscreen() const noexcept
	{
		// NIY;
		Logger::instance().log_error("Window_win32::isFullscreen() is not implemented yet!");
		return false;
	}

	void Window_win32::resizable(const bool state) const noexcept
	{
		// NIY;
		Logger::instance().log_error("Window_win32::resizable() is not implemented yet!");
	}

	void Window_win32::borderless(const bool state ) const noexcept
	{
		// NIY;
		Logger::instance().log_error("Window_win32::borderless() is not implemented yet!");
	}

	vec2ui Window_win32::mousePosition() const noexcept
	{
		POINT position {};
		GetCursorPos(&position);
		ScreenToClient(hWnd_, &position);
		return { static_cast<uint>(position.x), static_cast<uint>(position.y) };
	}

	void Window_win32::setMousePosition(const vec2ui& position) const noexcept
	{
		POINT pos { static_cast<LONG>(position.x), static_cast<LONG>(position.y) };
		ClientToScreen(hWnd_, &pos);
		SetCursorPos(pos.x, pos.y);
	}

	void Window_win32::clipMouse(const vec2ui& topLeft, const vec2ui& bottomRight) const noexcept
	{
		RECT rect { static_cast<LONG>(topLeft.x), static_cast<LONG>(topLeft.y), static_cast<LONG>(bottomRight.x), static_cast<LONG>(bottomRight.y) };
		ClipCursor(&rect);
	}

	std::array<vec2ui, 2> Window_win32::mouseClipArea() const noexcept
	{
		RECT rect {};
		GetClipCursor(&rect);
		vec2ui topLeft { static_cast<uint>(rect.left), static_cast<uint>(rect.top) };
		vec2ui bottomRight { static_cast<uint>(rect.right), static_cast<uint>(rect.bottom) };
		return { topLeft, bottomRight };
	}

	void Window_win32::showMouse(const bool state) const noexcept
	{
		ShowCursor(state);
	}

	bool Window_win32::isMouseVisible() const noexcept
	{
		CURSORINFO info {};
		GetCursorInfo(&info);
		return (info.flags == CURSOR_SHOWING);
	}

	bool Window_win32::isResizable() const noexcept
	{
		// NIY;
		Logger::instance().log_error("Window_win32::isResizable() is not implemented yet!");
		return false;
	}

	bool Window_win32::isBorderless() const noexcept
	{
		// NIY;
		Logger::instance().log_error("Window_win32::isBorderless() is not implemented yet!");
		return false;
	}

	vec2ui Window_win32::clientSize() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to get window client size, window is already closed -> returning {0, 0}");
			return { 0, 0 };
		}

		RECT rect {};
		GetClientRect(hWnd_, &rect);

		return { static_cast<uint>(rect.right) - static_cast<uint>(rect.left), static_cast<uint>(rect.bottom) - static_cast<uint>(rect.top) };
	}

	vec2ui Window_win32::position() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to get window position, window is already closed -> returning {0, 0}");
			return { 0, 0 };
		}

		RECT rect {};
		GetWindowRect(hWnd_, &rect);

		return { static_cast<uint>(rect.left), static_cast<uint>(rect.top) };
	}

	vec2ui Window_win32::size() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to get window size, window is already closed -> returning {0, 0}");
			return { 0, 0 };
		}

		RECT rect {};
		GetWindowRect(hWnd_, &rect);

		return { static_cast<uint>(rect.right) - static_cast<uint>(rect.left), static_cast<uint>(rect.bottom) - static_cast<uint>(rect.top) };
	}

	void Window_win32::setPosition(const vec2ui& position) const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to set window position, window is already closed");
		}
		else
		{
			SetWindowPos(hWnd_, nullptr, position.x, position.y, 0, 0, SWP_NOSIZE);
		}
	}

	void Window_win32::setSize(const vec2ui& size) const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to set window size, window is already closed");
		}
		else
		{
			SetWindowPos(hWnd_, nullptr, 0, 0, size.x, size.y, SWP_NOMOVE);
		}
	}

	std::string Window_win32::title() const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to get window title, window is already closed, returning \"noTitle\"");
			return { "noTitle" };
		}

		char buffer[256];
		GetWindowTextA(hWnd_, buffer, sizeof(buffer));
		return { buffer };
	}

	void Window_win32::setTitle(const std::string& title) const noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to set window title, window is already closed");
		}
		else
		{
			SetWindowTextA(hWnd_, title.c_str());
		}
	}

	void Window_win32::setIcon(const std::string& path) noexcept
	{
		if (isClosed())
		{
			Logger::instance().log_warning("Unable to set window icon, window is already closed");
		}
		else
		{
			HANDLE handle = LoadImageA(nullptr, path.c_str(), IMAGE_ICON, 0, 0, LR_DEFAULTSIZE | LR_LOADFROMFILE);
			if (handle)
			{
				if (hIcon_)
				{
					DestroyIcon(static_cast<HICON>(hIcon_));
				}
				hIcon_ = handle;

				PostMessage(hWnd_, WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon_));
				PostMessage(hWnd_, WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon_));

				PostMessage(GetWindow(hWnd_, GW_OWNER), WM_SETICON, ICON_SMALL, reinterpret_cast<LPARAM>(hIcon_));
				PostMessage(GetWindow(hWnd_, GW_OWNER), WM_SETICON, ICON_BIG, reinterpret_cast<LPARAM>(hIcon_));
			}
			else
			{
				Logger::instance().log_warning("Unable to set window icon, check the file location or the extension. Currently only supports .ICO file extensions");
			}
		}
	}

	void Window_win32::s_getModuleHandle_()
	{
		s_hInstance_ = GetModuleHandle(nullptr);
		if (!s_hInstance_)
		{
			throw RuntimeException("Unable to get the module handle.");
		}
	}

	void Window_win32::s_registerWindowclass_()
	{
		if (!s_registered_)
		{
			WNDCLASSEXA wc {};
			wc.cbSize = sizeof(wc);
			wc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;
			wc.lpfnWndProc = static_cast<WNDPROC> (Window_win32::windowProc_callback_);
			wc.cbClsExtra = 0;
			wc.cbWndExtra = 0;
			wc.hInstance = s_hInstance_;
			wc.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
			wc.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
			wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
			wc.hbrBackground = nullptr;
			wc.lpszMenuName = nullptr;
			wc.lpszClassName = WINDOW_CLASS_NAME.c_str();

			if (!RegisterClassExA(&wc))
			{
				throw RuntimeException("Unable to register the window class.");
			}
			s_registered_ = true;
		}
	}

	Window_win32* Window_win32::s_getWindow_(const HWND& hwnd)
	{
		auto window = s_handles_[hwnd];
		if (!window)
		{
			RuntimeException("Unable to get the window handle. The requested window handle is not registered or destroyed already");
		}
		return window;
	}

	LRESULT CALLBACK Window_win32::windowProc_callback_(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		auto window = s_getWindow_(hwnd);
		if (window)
		{
			switch (msg)
			{
				case WM_CREATE:
				{
					window->signal_create.emit();
					break;
				}
				case WM_SHOWWINDOW:
				{
					if (static_cast<bool>(wparam))
					{
						window->signal_show.emit();
					}
					else
					{
						window->signal_hide.emit();
					}
					break;
				}
				case WM_SETFOCUS:
				{
					window->signal_focus.emit();
					break;
				}
				case WM_KILLFOCUS:
				{
					window->signal_unfocus.emit();
					break;
				}
				case WM_CLOSE:
				{
					window->signal_close.emit();
					break;
				}
				case WM_DESTROY:
				{
					window->signal_destroy.emit();
					break;
				}
				case WM_MOVE:
				{
					auto posX = static_cast<uint>(LOWORD(lparam));
					auto posY = static_cast<uint>(HIWORD(lparam));
					vec2ui pos { posX, posY };
					window->signal_move.emit(pos);
					break;
				}
				case WM_SIZE:
				{
					auto width = static_cast<uint>(LOWORD(lparam));
					auto height = static_cast<uint>(HIWORD(lparam));
					vec2ui windowSize { width, height };
					window->signal_resize.emit(windowSize);
					break;
				}
				case WM_SYSKEYDOWN:
				case WM_KEYDOWN:
				{
					KeyboardEvent e;
					e.key = KeyboardTranslator_win32::translate(static_cast<uint>(wparam));
					s_processInputEvent_(&e, window);
					window->signal_keyboardButtonDown.emit(e);
					break;
				}
				case WM_SYSKEYUP:
				case WM_KEYUP:
				{
					KeyboardEvent e;
					e.key = KeyboardTranslator_win32::translate(static_cast<uint>(wparam));
					s_processInputEvent_(&e, window);
					window->signal_keyboardButtonUp.emit(e); 
					break;
				}
				case WM_LBUTTONDOWN:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_LEFT;
					s_processInputEvent_(&e, window);
					window->signal_mouseButtonDown.emit(e);
					break;
				}
				case WM_LBUTTONUP:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_LEFT;
					s_processInputEvent_(&e, window);
					window->signal_mouseButtonUp.emit(e);
					break;
				}
				case WM_RBUTTONDOWN:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_RIGHT;
					s_processInputEvent_(&e, window);
					window->signal_mouseButtonDown.emit(e);
					break;
				}
				case WM_RBUTTONUP:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_RIGHT;
					s_processInputEvent_(&e, window);
					window->signal_mouseButtonUp.emit(e);
					break;
				}
				case WM_MBUTTONDOWN:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_MIDDLE;
					s_processInputEvent_(&e, window);
					window->signal_mouseButtonDown.emit(e);
					break;
				}
				case WM_MBUTTONUP:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_MIDDLE;
					s_processInputEvent_(&e, window);
					window->signal_mouseButtonUp.emit(e);
					break;
				}
				case WM_XBUTTONDOWN:
				{
					MouseEvent e;
					if (HIWORD(wparam == 1))
					{
						e.key = MouseKey::MOUSE_EXTRA1;
					}
					else
					{
						e.key = MouseKey::MOUSE_EXTRA2;
					}
					s_processInputEvent_(&e, window);
					window->signal_mouseButtonDown.emit(e);
					break;
				}
				case WM_XBUTTONUP:
				{
					MouseEvent e;
					if (HIWORD(wparam == 1))
					{
						e.key = MouseKey::MOUSE_EXTRA1;
					}
					else
					{
						e.key = MouseKey::MOUSE_EXTRA2;
					}
					s_processInputEvent_(&e, window);
					window->signal_mouseButtonUp.emit(e);
					break;
				}
				case WM_LBUTTONDBLCLK:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_LEFT;
					s_processInputEvent_(&e, window);
					window->signal_mouseDoubleClick.emit(e);
					break;
				}
				case WM_RBUTTONDBLCLK:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_RIGHT;
					s_processInputEvent_(&e, window);
					window->signal_mouseDoubleClick.emit(e);
					break;
				}
				case WM_MBUTTONDBLCLK:
				{
					MouseEvent e;
					e.key = MouseKey::MOUSE_MIDDLE;
					s_processInputEvent_(&e, window);
					window->signal_mouseDoubleClick.emit(e);
					break;
				}
				case WM_MOUSEWHEEL:
				{
					MouseEvent e;
					e.wheel = GET_WHEEL_DELTA_WPARAM(wparam) / 120;
					s_processInputEvent_(&e, window);
					window->signal_mouseWheel.emit(e);
					break;
				}
				case WM_MOUSEMOVE:
				{
					MouseEvent e;
					s_processInputEvent_(&e, window);
					window->signal_mouseMove.emit(e);
					break;
				}
			}
		}
		return DefWindowProc(hwnd, msg, wparam, lparam);
	}

	void Window_win32::s_processInputEvent_(InputEvent* e, Window_win32* window)
	{
		if (GetKeyState(VK_MENU) & 0x8000)
		{
			e->alt = true;
		}
		if (GetKeyState(VK_CONTROL) & 0x8000)
		{
			e->ctrl = true;
		}
		if (GetKeyState(VK_SHIFT) & 0x8000)
		{
			e->shift = true;
		}
		if (GetKeyState(VK_LWIN) & 0x8000 || GetKeyState(VK_RWIN) & 0x800)
		{
			e->windows = true;
		}

		e->position = window->mousePosition();
	}
}