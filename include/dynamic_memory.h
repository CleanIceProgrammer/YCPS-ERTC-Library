#pragma once

#include <memory>

namespace dynamic_memory {

template <typename T>
using DyPtr = std::shared_ptr<T>;

}
