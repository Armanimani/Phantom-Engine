#pragma once

#include <cstdint>
#include "math/math.hpp"

namespace phantom::core
{
	using int8 = int8_t;
	using int16 = int16_t;
	using int32 = int32_t;
	using int64 = int64_t;

	using uint8 = uint8_t;
	using uint16 = uint16_t;
	using uint32 = uint32_t;
	using uint64 = uint64_t;

	using Byte = int8;
	using uint = uint32;
	using ushort = uint8;

	using vec2 = Vector2<float>;
	using vec2f = vec2;
	using vec2i = Vector2<int32>;
	using vec2ui = Vector2<uint>;
	using vec2us = Vector2<ushort>;
}