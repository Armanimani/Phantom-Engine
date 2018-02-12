#include "Application.hpp"

#include "../exceptions/Exception.hpp"
#include "../logger/Logger.hpp"

namespace phantom::core
{
	Application::Application(std::unique_ptr<Settings>& settings)
	{
		try
		{
			Logger::instance();
			Logger::instance().setLogToFile(true);

			settings_ = std::move(settings->application);
			timer_ = std::make_unique<Timer>();
			window_ = std::make_unique<Window>(settings->window);
			input_ = std::make_unique<InputManager>();
			event_connectToSender(window_.get());
			input_->event_connectToSender(window_.get());
			input_->context.link_keyboardDown(KeyboardKey::KEY_ESCAPE, Slot<void(void)>(this, &Application::stop));
		}
		catch (IException& e)
		{
			Logger::instance().log_error(e.what());
			throw;
		}
	}

	Application::~Application()
	{
		Logger::instance().log_status("Shutting down..."); // Q: Is logger destructed after the app or not ?
	}

	void Application::start()
	{
		running_ = true;
		paused_ = false;
		
		try
		{
			if (!initialized_)
			{
				systemInit_();
			}
			init_();
			window_->create();
			run_();
		}
		catch (IException& e)
		{
			Logger::instance().log_error(e.what());
		}
	}

	void Application::pause() noexcept
	{
		paused_ = true;
	}

	void Application::resume() noexcept
	{
		paused_ = false;
	}

	void Application::stop() noexcept
	{
		running_ = false;
	}

	uint Application::getFPS() const noexcept
	{
		return FPS_;
	}

	uint Application::getUPS() const noexcept
	{
		return UPS_;
	}


	void Application::init_()
	{
		appInit_();
	}


	void Application::run_()
	{
		Logger::instance().log_status("Starting...");

		window_->show();

		float elapsedTime { 0.0f };
		uint updateCounter { 0 };
		uint frameCounter { 0 };

		timer_->reset();
		auto now = timer_->time();
		TimeStep updateTimeStep(now);
		TimeStep timeStep(now);

		while (running_)
		{
			window_->clear();

			auto now = timer_->time();
			if (updateTimeStep.deltaTime_s(now) >= settings_->updateFrequency)
			{
				window_->update();
				if (!paused_)
				{
					update_(updateTimeStep.deltaTime_s(now));
					updateTimeStep.update(now);
					updateCounter++;
				}
			}

			render_();
			frameCounter++;

			if (timeStep.deltaTime_s(now) >= 1.0f)
			{
				elapsedTime += timeStep.deltaTime_s();
				timeStep.update(now);

				FPS_ = frameCounter;
				UPS_ = updateCounter;

				frameCounter = 0;
				updateCounter = 0;
				secondUpdate_();
			}
		}
	}

	void Application::update_(const float dt_s)
	{
		appUpdate_();
	}

	void Application::secondUpdate_()
	{
		appSecondUpdate_();
	}

	void Application::render_()
	{
		appRender_();
	}

	void Application::systemInit_()
	{
		Logger::instance().log_status("Initializing...");

		window_->create();
		initialized_ = true;
	}
}