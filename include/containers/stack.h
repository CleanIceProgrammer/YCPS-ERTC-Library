#pragma once

#include <vector>

#include "dynamic_memory.h"
#include "object.h"
#include "iterator/iterable.h"
#include "exceptions.h"
#include "extint.h"

namespace containers {

using dynamic_memory::DyPtr;
using obj::R_Object;
using obj::newobj;
using obj::objcast;
using iter::R_IIterable;
using iter::R_IIterator;
using iter::IIterator;
using exc::NoNextIteratorException;
using exc::OutOfRangeException;
using namespace ext_int;

template <typename EleType>
class R_Stack;

template <typename EleType>
using Stack = DyPtr<R_Stack<EleType>>;

template <typename EleType>
class R_Stack : public R_Object, public R_IIterable<typename std::vector<EleType>::iterator, typename std::vector<EleType>::const_iterator, EleType> {
private:
    std::vector<EleType> value;

public:
    class R_Iterator;
    
    using Iterator = DyPtr<R_Iterator>;
    
    using LangIterator = std::vector<EleType>::iterator;
    using ConstLangIterator = std::vector<EleType>::const_iterator;
    
    R_Stack() noexcept;
    
    //* ----- impl IIterable -----
    inline IIterator<EleType> iterator() const noexcept override;
    inline LangIterator lang_iterator() noexcept override;
    inline LangIterator begin() noexcept override;
    inline LangIterator end() noexcept override;
    inline ConstLangIterator cbegin() const noexcept override;
    inline ConstLangIterator cend() const noexcept override;
    //* ----- end [impl IIterable] -----
    
    inline void push(EleType ele) noexcept;
    inline EleType pop();
    inline EleType top() const;
    inline size_type size() const noexcept;
    inline bool empty() const noexcept;
    inline void clear() noexcept;
};

template <typename EleType>
class R_Stack<EleType>::R_Iterator : public R_IIterator<EleType> {
private:
    const std::vector<EleType>& stack;
    size_type now = 0;
    
public:
    R_Iterator(const std::vector<EleType>& stack_value) noexcept;
    
    //* ----- impl IIterator -----
    EleType get_value() const override;
    bool has_next() const noexcept override;
    void next() override;
    //* ----- end [impl IIterator] -----
};

//* implementations

//* ----- impl R_Stack -----

template <typename EleType>
R_Stack<EleType>::R_Stack() noexcept { }

template <typename EleType>
inline IIterator<EleType> R_Stack<EleType>::iterator() const noexcept {
    return objcast<IIterator<EleType>>(newobj<Iterator>(value));
}

template <typename EleType>
inline R_Stack<EleType>::LangIterator R_Stack<EleType>::lang_iterator() noexcept {
    return value.begin();
}

template <typename EleType>
inline R_Stack<EleType>::LangIterator R_Stack<EleType>::begin() noexcept {
    return value.begin();
}

template <typename EleType>
inline R_Stack<EleType>::LangIterator R_Stack<EleType>::end() noexcept {
    return value.end();
}

template <typename EleType>
inline R_Stack<EleType>::ConstLangIterator R_Stack<EleType>::cbegin() const noexcept {
    return value.cbegin();
}

template <typename EleType>
inline R_Stack<EleType>::ConstLangIterator R_Stack<EleType>::cend() const noexcept {
    return value.cend();
}

template <typename EleType>
inline void R_Stack<EleType>::push(EleType ele) noexcept {
    value.push_back(ele);
}

template <typename EleType>
inline EleType R_Stack<EleType>::pop() {
    if (empty()) {
        throw newobj<OutOfRangeException>();
    }
    EleType temp = value.back();
    value.pop_back();
    return temp;
}

template <typename EleType>
inline EleType R_Stack<EleType>::top() const {
    if (empty()) {
        throw newobj<OutOfRangeException>();
    }
    return value.back();
}

template <typename EleType>
inline size_type R_Stack<EleType>::size() const noexcept {
    return value.size();
}

template <typename EleType>
inline bool R_Stack<EleType>::empty() const noexcept {
    return size() == 0;
}

template <typename EleType>
inline void R_Stack<EleType>::clear() noexcept {
    value.clear();
    value.shrink_to_fit();
}

//* ----- end [impl R_Stack] -----

//* ----- impl R_Stack::R_Iterator -----

template <typename EleType>
R_Stack<EleType>::R_Iterator::R_Iterator(const std::vector<EleType>& stack_value) noexcept :
    stack(stack_value) { }

template <typename EleType>
EleType R_Stack<EleType>::R_Iterator::get_value() const {
    if (now >= stack.size()) {
        throw newobj<OutOfRangeException>();
    }
    return stack[now];
}

template <typename EleType>
bool R_Stack<EleType>::R_Iterator::has_next() const noexcept {
    return now < stack.size() - 1;
}

template <typename EleType>
void R_Stack<EleType>::R_Iterator::next() {
    if (!has_next()) {
        throw newobj<NoNextIteratorException>();
    }
    now++;
}

//* ----- end [impl R_Stack::R_Iterator] -----

}
