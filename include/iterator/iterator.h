#pragma once

#include <memory>

#include "dynamic_memory.h"
#include "object.h"

namespace iter {

using dynamic_memory::DyPtr;
using obj::R_Object;

template <typename ValueType>
class R_Iterator;

/// @brief Iterator [接口]
/// @tparam ValueType 值的类型
template <typename ValueType>
using Iterator = DyPtr<R_Iterator<ValueType>>;

/// @brief R_Iterator [接口] {不建议使用}
/// @tparam ValueType 值的类型
template <typename ValueType>
class R_Iterator : R_Object<R_Iterator> {
public:
    virtual const ValueType& get_value() const noexcept = 0;
    virtual ValueType& get_value() = 0;
    virtual void remove() = 0;
    virtual bool has_next() const noexcept = 0;
    virtual void next() = 0;
};

}
