#pragma once

#include <concepts>

#include "iterator/iterator.h"
#include "dynamic_memory.h"

namespace iter {

using dynamic_memory::DyPtr;

template <typename Type>
concept LangIteratorType = requires(Type a, Type b) {
    a++;
    *a;
    a == b;
    a != b;
};

template <typename LangIterator, typename ConstLangIterator, typename ValueType>
requires LangIteratorType<LangIterator> && LangIteratorType<ConstLangIterator>
class R_IIterable;

template <typename LangIterator, typename ConstLangIterator, typename ValueType>
requires LangIteratorType<LangIterator> && LangIteratorType<ConstLangIterator>
using IIterable = DyPtr<R_IIterable<LangIterator, ConstLangIterator, ValueType>>;

template <typename LangIterator, typename ConstLangIterator, typename ValueType>
requires LangIteratorType<LangIterator> && LangIteratorType<ConstLangIterator>
class R_IIterable {
public:
    inline virtual IIterator<ValueType> iterator() const noexcept = 0;
    inline virtual LangIterator lang_iterator() noexcept = 0;
    inline virtual LangIterator begin() noexcept = 0;
    inline virtual LangIterator end() noexcept = 0;
    inline virtual ConstLangIterator cbegin() const noexcept = 0;
    inline virtual ConstLangIterator cend() const noexcept = 0;
};

}
