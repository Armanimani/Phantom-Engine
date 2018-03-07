#include "System_win32.hpp"

#include "../../exceptions/Exception.hpp"

#include <windows.h>
#include <psapi.h>

namespace phantom::core
{

	std::unique_ptr<phantom::core::SystemMemoryInformation> System_win32::memory() const noexcept
	{
		auto ret = std::make_unique<SystemMemoryInformation>();

		MEMORYSTATUSEX statex {};
		statex.dwLength = sizeof(statex);
		GlobalMemoryStatusEx(&statex);
		ret->total_physicalMemory = static_cast<uint64>(statex.ullTotalPhys);
		ret->free_physicalMemory = static_cast<uint64>(statex.ullAvailPhys);
		ret->used_physicalMemory = static_cast<uint64>(statex.ullTotalPhys - statex.ullAvailPhys);
		ret->total_virtualMemory = static_cast<uint64>(statex.ullTotalPageFile);
		ret->free_virtualMemory = static_cast<uint64>(statex.ullAvailPageFile);
		ret->used_virtualMemory = static_cast<uint64>(statex.ullTotalPageFile - statex.ullAvailPageFile);

		PROCESS_MEMORY_COUNTERS pmc {};
		GetProcessMemoryInfo(GetCurrentProcess(), &pmc, sizeof(pmc));
		ret->app_physicalMemory = static_cast<uint64>(pmc.WorkingSetSize);
		ret->app_virtualMemory = static_cast<uint64>(pmc.PagefileUsage);

		return std::move(ret);
	}

	std::string System_win32::temporaryPath() const
	{
		TCHAR buffer[MAX_PATH];
		if (!GetTempPath(MAX_PATH, buffer))
		{
			throw FileNotFoundException("Unable to get the temporary directory for windows");
		}

		return { buffer };
	}

}