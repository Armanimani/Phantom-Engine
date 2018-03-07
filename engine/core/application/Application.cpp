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
			system_ = std::make_unique<System>();
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

	float Application::getLastDrawTime() const noexcept
	{
		return lastDrawTime_;
	}

	float Application::getLastLogicTime() const noexcept
	{
		return lastLogicTime_;
	}


	void Application::init_()
	{
		system_->init();
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
		TimeStep drawTimeStep(now);

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
		TimeStep timeStep(timer_->time());
		appUpdate_();
		timeStep.update(timer_->time());
		lastLogicTime_ = timeStep.deltaTime_ms();
	}

	void Application::secondUpdate_()
	{
		appSecondUpdate_();
	}

	void Application::render_()
	{
		TimeStep timeStep(timer_->time());
		appRender_();
		timeStep.update(timer_->time());
		lastDrawTime_ = timeStep.deltaTime_ms();
	}

	void Application::systemInit_()
	{
		Logger::instance().log_status("Initializing...");
		
		log_systemInformation_();

		window_->create();
		initialized_ = true;
	}

	void Application::log_systemInformation_() const noexcept
	{
		std::string system { "*****System Information*****\n" };
		const float B_MB = 1.0f / 1024.0f / 1024.0f;
		auto mem = system_->memory();
		std::string memory { "-Memory:\n\t-Physical Memory:\n\t\tTotal:  " + std::to_string(mem->total_physicalMemory * B_MB) + "MB\n\t\tFree:  " + std::to_string(mem->free_physicalMemory * B_MB) + "MB / " + std::to_string(static_cast<float>(mem->free_physicalMemory) / static_cast<float>(mem->total_physicalMemory) * 100.0f) + "%\n\t\tUsed:  " + std::to_string(mem->used_physicalMemory * B_MB) + "MB / " + std::to_string(static_cast<float>(mem->used_physicalMemory) / static_cast<float>(mem->total_physicalMemory) * 100.0f) + "%\n\t\tApp:  " + std::to_string(mem->app_physicalMemory * B_MB) + "MB\n\t-Virtual Memory:\n\t\tTotal:  " + std::to_string(mem->total_virtualMemory * B_MB) + "MB\n\t\tFree:  " + std::to_string(mem->free_virtualMemory * B_MB) + "MB / " + std::to_string(static_cast<float>(mem->free_virtualMemory) / static_cast<float>(mem->total_virtualMemory) * 100.0f) + "%\n\t\tUsed:  " + std::to_string(mem->used_virtualMemory * B_MB) + "MB / " + std::to_string(static_cast<float>(mem->used_virtualMemory) / static_cast<float>(mem->total_virtualMemory) * 100.0f) + "%\n\t\tApp:  " + std::to_string(mem->app_virtualMemory * B_MB) + "MB\n" };

		std::string paths { "-Paths:\n\t-Temporary Directory: " + system_->temporaryPath() };

		Logger::instance().log_information(system + memory + paths);
	}

}