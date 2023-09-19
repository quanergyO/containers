#include <iostream>
#include "conditional.h"

template <typename T>
class Vector
{
private:
    T* arr;
    size_t size_;
    size_t capacity_;
public:

    template<bool isConst>
    struct common_iterator {
    private:
        conditional_t<isConst, const T*, T*> ptr;
    public:
        common_iterator(T* ptr) : ptr(ptr) {}

        conditional_t<isConst, const T*, T*>& operator*()
        {
            return *ptr;
        }

        conditional_t<isConst, const T*, T*>* operator->()
        {
            return ptr;
        }

        common_iterator& operator++()
        {
            ++ptr;
            return *this;
        }

        common_iterator& operator++(int)
        {
            T* returnValue = ptr;
            ++ptr;
            return returnValue;
        }
    };

    using iterator = common_iterator<true>;
    using const_iterator = common_iterator<false>;

    iterator begin() const noexcept
    {
        return iterator(arr);
    }

    iterator end() const noexcept
    {
        return iterator(arr+size_);
    }

    iterator rbegin() const noexcept
    {
        return iterator(arr+size_-1);
    }

    iterator rend() const noexcept
    {
        return iterator(arr-1);
    }

    size_t size() const noexcept
    {
        return size_;
    }

    size_t capacity() const noexcept
    {
        return capacity_;
    }

};
