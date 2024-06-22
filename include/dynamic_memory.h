#pragma once

#include <memory>

namespace dynamic_memory {

/// @brief DyPtr [type alias] | DyPtr [类型别名]
/// @tparam T the type | 类型
template <typename T>
using DyPtr = std::shared_ptr<T>;

}
