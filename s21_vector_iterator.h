#ifndef S21_VECTOR_ITERATOR_H_
#define S21_VECTOR_ITERATOR_H_

#include "conditional.h"

namespace S21
{

template <typename T>
template <bool IsConst>
struct CommonIterator
{
private:
    using iterator = CommonIterator<false>;
    using const_iterator = CommonIterator<true>;
    using ConditionalValueType = conditional_t<IsConst, const T, T>;
    using ConditionalPtr = conditional<IsConst, const T*, T*>;
    using ConditionalReference = conditional<IsConst, const T&, T&>;

    ConditionalPtr ptr_;
public:
    CommonIterator<IsConst>& operator+=(int n)
    {
        ptr_ += n;
        return *this;
    }

    CommonIterator<IsConst> operator+(int n)
    {
        iterator copy = *this;
        copy += n;
        return copy;
    }

    ConditionalReference operator*()
    {
        return *ptr_;
    }

    ConditionalPtr operator->()
    {
        return ptr_;
    }

};

} // namespace S21

#endif // S21_VECTOR_ITERATOR_H_
