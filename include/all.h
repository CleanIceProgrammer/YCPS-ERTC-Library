#pragma once

#include "object.h"
#include "dynamic_memory.h"
#include "stack.h"

namespace cldl_std {

//* object.h
using obj::R_Object;
using obj::Object;
using obj::ObjectType;
using obj::newobj;

//* dynamic_memory.h
using dynamic_memory::DyPtr;

//* stack.h
using containers::R_Stack;
using containers::Stack;

}
