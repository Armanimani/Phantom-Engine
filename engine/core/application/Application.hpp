#pragma once

#include "Settings.hpp"
#include "../timer/Timer.hpp"
#include "../window/Window.hpp"
#include "../event/window/WindowEventListener.hpp"
#include "../input/InputManager.hpp"
#include "../system/system.hpp"

namespace phantom::core
{
	class Application : private WindowEventListener
	{
	public:
		explicit Application(std::unique_ptr<Settings>& settings);
		~Application();

		void start();
		void pause() noexcept;
		void resume() noexcept;
		void stop() noexcept;

	protected:
		std::unique_ptr<InputManager> input_ {};
		std::unique_ptr<Window> window_ {};

		uint getFPS() const noexcept;
		uint getUPS() const noexcept;
		float getLastDrawTime() const noexcept;
		float getLastLogicTime() const noexcept;

		virtual void appInit_() {};
		virtual void appRender_() {};
		virtual void appUpdate_() {};
		virtual void appSecondUpdate_() {};

	private:
		std::unique_ptr<ApplicationSettings> settings_ {};
		std::unique_ptr<Timer> timer_ {};
		std::unique_ptr<System> system_ {};

		bool initialized_ { false };
		bool running_ { false };
		bool paused_ { false };

		uint FPS_ {};
		uint UPS_ {};
		float lastDrawTime_ {};
		float lastLogicTime_ {};

		void init_();
		void run_();
		void update_(float dt_s);
		void secondUpdate_();
		void render_();

		void systemInit_();
		void log_systemInformation_() const noexcept;
	};
}