#pragma once

#include "../logger/Logger.hpp"

#include <vector>
#include <algorithm>

namespace phantom::core
{
	template <typename Slot>
	class Signal
	{
	public:
		using SlotType_t = Slot;
		using Type_t = Signal<Slot>;

		void connect(Slot& slot)
		{
			if (std::find(slots_.cbegin(), slots_.cend(), &slot) == slots_.cend())
			{
				slots_.push_back(&slot);
			}
			else
			{
				Logger::instance().log_warning("Unable to connect the requested slot. The slot is already connected.");
			}
		}

		void disconnect(Slot& slot)
		{
			if (auto i = std::find(slots_.cbegin(), slots_.cend(), &slot) == slots_.cend())
			{
				slots_.erase(slots_.begin() + i);
			}
			else
			{
				Logger::instance().log_warning("Unable to remove the requested slot. The slot is not connected to this signal.");
			}
		}

		template <typename ...Args>
		void emit(Args&&... args) const
		{
			for (auto i = slots_.cbegin(); i != slots_.cend(); i++)
			{
				if ((*i) == nullptr)
				{
					Logger::instance().log_warning("Accessing a nullptr slot through the signal!");
				}
				else
				{
					(**i)(std::forward<Args>(args)...);
				}
			}
		}

		void clear()
		{
			slots_.clear();
		}

		template <typename ...Args>
		void operator()(Args&&... args) const
		{
			emit(std::forward<Args>(args)...);
		}

	protected:
		std::vector<SlotType_t*> slots_;
	};
}