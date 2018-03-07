#pragma once

#include <memory>

namespace phantom::core
{
	struct SystemMemoryInformation
	{
		uint64 total_physicalMemory { 1 };
		uint64 free_physicalMemory { 0 };
		uint64 used_physicalMemory { 0 };
		uint64 app_physicalMemory { 0 };

		uint64 total_virtualMemory { 1 };
		uint64 free_virtualMemory { 0 };
		uint64 used_virtualMemory { 0 };
		uint64 app_virtualMemory { 0 };
	};
}