#pragma once

#include <concepts>

#include "iterator/iterator.h"

namespace iter {

template <typename Type>
concept HasLangIterator = requires {
    typename Type::LangIterator;
};

/// interface
template <HasLangIterator ChildType>
class R_Iterable {
public:
    virtual Iterator<ValueType> iterator() noexcept = 0;
    virtual typename ChildType::LangIterator lang_iterator() noexcept = 0;
    virtual typename ChildType::LangIterator begin() noexcept = 0;
    virtual typename ChildType::LangIterator end() noexcept = 0;
    virtual const typename ChildType::LangIterator cbegin() noexcept = 0;
    virtual const typename ChildType::LangIterator cend() noexcept = 0;
};

}
