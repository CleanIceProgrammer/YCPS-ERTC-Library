#pragma once

#include <exception>
#include <stdexcept>

#include "iterator/exceptions.h"
#include "dynamic_memory.h"

namespace exc {

using dynamic_memory::DyPtr;

class R_OutOfRangeException;

using OutOfRangeException = DyPtr<R_OutOfRangeException>;

class R_OutOfRangeException : public std::out_of_range {
public:
    R_OutOfRangeException() noexcept;
    const char* what() const noexcept override;
};

}
