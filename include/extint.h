#pragma once

#include <cstdint>
#include <utility>

namespace ext_int {

using byte = std::uint8_t;
using sbyte = std::int8_t;
using int8 = std::int8_t;
using uint8 = std::uint8_t;
using int16 = std::int16_t;
using uint16 = std::uint16_t;
using int32 = std::int32_t;
using uint32 = std::uint32_t;
using int64 = std::int64_t;
using uint64 = std::uint64_t;

#ifdef __SIZEOF_INT128__
using int128 = __int128_t;
using uint128 = __uint128_t;
#endif  // __SIZEOF_INT128__

using size_type = std::size_t;
using ssize_type = ssize_t;

using sys_int = int;

using pointer = void*;

}
