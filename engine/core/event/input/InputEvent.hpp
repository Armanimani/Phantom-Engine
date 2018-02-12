#pragma once

#include "../../common.hpp"

namespace phantom::core
{
	struct InputEvent
	{
		bool alt { false };
		bool ctrl { false };
		bool shift { false };
		bool windows { false };

		vec2ui position {};
	};
}