#pragma once

#include "../common.hpp"
#include "SystemMemoryInformation.hpp"

#include <memory>
#include <string>

namespace phantom::core
{
	class ISystem
	{
	public:
		virtual std::unique_ptr<SystemMemoryInformation> memory() const noexcept = 0;

		void init() noexcept
		{
			auto mem = memory();
			initial_physicalMemory_ = mem->app_physicalMemory;
			initial_virtualMemory_ = mem->app_virtualMemory;
		}

		uint64 totalAllocation() { return initial_virtualMemory_ + initial_physicalMemory_; }
		uint64 totalPhysicalMemoryAllocation() { return initial_physicalMemory_; }
		uint64 totalVirtualMemoryAllocation() { return initial_virtualMemory_; }

		virtual std::string temporaryPath() const = 0;
	private:
		uint64 initial_physicalMemory_ {};
		uint64 initial_virtualMemory_ {};
	};
}