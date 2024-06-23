#pragma once

#include "object.h"
#include "dynamic_memory.h"
#include "exceptions.h"
#include "extint.h"

#include "containers/stack.h"

#include "iterator/iterator.h"
#include "iterator/iterable.h"

namespace ertc_std {

//* object.h
using obj::R_Object;
using obj::Object;
using obj::ObjectType;
using obj::newobj;
using obj::objcast;
#ifdef __ERTC_NULL
using obj::null_type;
using obj::null;
#endif  // __ERTC_NULL

//* dynamic_memory.h
using dynamic_memory::DyPtr;

//* exceptions.h
using exc::R_NoNextIteratorException;
using exc::NoNextIteratorException;
using exc::R_OutOfRangeException;
using exc::OutOfRangeException;

//* extint.h
using ext_int::byte;
using ext_int::sbyte;
using ext_int::int8;
using ext_int::uint8;
using ext_int::int16;
using ext_int::uint16;
using ext_int::int32;
using ext_int::uint32;
using ext_int::int64;
using ext_int::uint64;
using ext_int::size_type;
using ext_int::ssize_type;
using ext_int::pointer;
using ext_int::sys_int;
#ifdef __SIZEOF_INT128__
using ext_int::int128;
using ext_int::uint128;
#endif  // __SIZE_OF_INT128__

//* containers/stack.h
using containers::R_Stack;
using containers::Stack;

//* iterator/iterator.h
using iter::R_IIterator;
using iter::IIterator;

//* iterator/iterable.h
using iter::R_IIterable;
using iter::IIterable;

}
