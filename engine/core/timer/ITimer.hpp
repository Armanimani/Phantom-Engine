#pragma once

namespace phantom::core
{
	class ITimer
	{
	public:
		virtual void reset() noexcept = 0;
		virtual float time() noexcept = 0;
	};
}