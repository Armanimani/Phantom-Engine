#pragma once

#include <FastDelegate.hpp>
#include <vector>
#include <utility>

namespace phantom::core
{
	template<typename T>
	class Slot
	{
	public:
		using Type_t = Slot<T>;
		using SignatureType_t = T;

		//Slot() {};
		Slot(T function) : delegate_(function) {}
		template<typename Object, typename MemFnPtr>
		Slot(Object* obj, MemFnPtr ptr) : delegate_(obj, ptr) {}

		template<typename ...Args>
		auto operator()(Args&&... args) const
		{
			return delegate_(std::forward<Args>(args)...);
		}

	private:
		using Delegate_t = fastdelegate::FastDelegate<T>;
		Delegate_t delegate_;
	};
}