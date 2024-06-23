#pragma once

#include <exception>

#include "dynamic_memory.h"

namespace exc {

using dynamic_memory::DyPtr;

class R_NoNextIteratorException;

using NoNextIteratorException = DyPtr<R_NoNextIteratorException>;

class R_NoNextIteratorException : public std::exception {
};

}
