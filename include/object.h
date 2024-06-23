#pragma once

#include <typeinfo>
#include <concepts>

#include "dynamic_memory.h"
#include "extint.h"

namespace obj {

//* definitions
#ifdef __ERTC_NULL
using null_type = std::nullptr_t;
const null_type null = nullptr;
#endif  // __ERTC_NULL

using dynamic_memory::DyPtr;
using ext_int::pointer;

class R_Object;

using Object = DyPtr<R_Object>;

class R_Object {
public:
    inline virtual const pointer id() const noexcept final;
};

template <typename Type>
concept ObjectType = requires {
    typename Type::element_type;
    std::is_same_v<std::remove_cvref_t<Type>, DyPtr<typename Type::element_type>>;
};

//* implementations
inline const pointer R_Object::id() const noexcept {
    return (const pointer) this;
}

//* functions

template <typename Type, typename... Args>
requires ObjectType<Type>
inline DyPtr<typename Type::element_type> newobj(Args&&... args) {
    return std::make_shared<typename Type::element_type>(std::forward<Args>(args)...);
}

template <typename TargetType, typename ArgType>
requires ObjectType<TargetType> && ObjectType<ArgType>
inline TargetType objcast(const ArgType& arg) {
    return dynamic_pointer_cast<typename TargetType::element_type>(arg);
}

}
