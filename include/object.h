#pragma once

#include <typeinfo>
#include <concepts>

#include "dynamic_memory.h"

namespace obj {

using dynamic_memory::DyPtr;

/// @brief R_Object [类] {不建议使用}
class R_Object {
public:
    
};

/// @brief Object [类]
using Object = DyPtr<R_Object>;

template <typename Type>
concept ObjectType = std::is_same_v<std::remove_cvref_t<Type>, std::shared_ptr<typename Type::element_type>>;

template <ObjectType Type, typename... Args>
inline DyPtr<typename Type::element_type> newobj(Args&&... args) {
    return std::make_shared<typename Type::element_type>(std::forward<Args>(args)...);
}

}
