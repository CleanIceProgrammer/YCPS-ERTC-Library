#pragma once

#include "dynamic_memory.h"
#include "object.h"

namespace containers {

using dynamic_memory::DyPtr;
using obj::R_Object;

template <typename EleType>
class R_Stack : R_Object {
public:
    EleType ele;
    
    R_Stack() noexcept;
};

template <typename EleType>
using Stack = DyPtr<R_Stack<EleType>>;

template <typename EleType>
R_Stack<EleType>::R_Stack() noexcept  { }

}
