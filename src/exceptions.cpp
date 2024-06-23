#include "exceptions.h"

namespace exc {

R_OutOfRangeException::R_OutOfRangeException() noexcept : std::out_of_range("Out of range")  { }

const char* R_OutOfRangeException::what() const noexcept {
    return "Out of range. ";
}

}
