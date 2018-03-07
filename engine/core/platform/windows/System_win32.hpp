#pragma once

#include "../../system/ISystem.hpp"

namespace phantom::core
{
	class System_win32 : public ISystem
	{
	public:
		std::unique_ptr<SystemMemoryInformation> memory() const noexcept override;

		std::string temporaryPath() const override;
	};
}