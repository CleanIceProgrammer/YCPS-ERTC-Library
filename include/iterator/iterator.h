#pragma once

#include "object.h"
#include "dynamic_memory.h"

namespace iter {

using obj::Object;
using dynamic_memory::DyPtr;

template <typename ValueType>
class R_IIterator;

template <typename ValueType>
using IIterator = DyPtr<R_IIterator<ValueType>>;

template <typename ValueType>
class R_IIterator {
public:
    virtual ValueType get_value() const = 0;
    virtual bool has_next() const noexcept = 0;
    virtual void next() = 0;
};

}
