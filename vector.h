#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include "allocator.h"
#include "conditional.h"
#include "iterator.h"

namespace S21
{

    template <typename T, typename Allocator = Allocator<T>>
    class Vector
    {
    public:
        template <bool IsConst>
        struct CommonIterator;
    private:
        T* data_;
        size_t size_;
        size_t capacity_;
        Allocator allocator_;

    public:
        using value_type = T;
        using allocator_type = Allocator;
        using size_type = size_t;
        using iterator = RandomAccessIterator<T>;

        explicit Vector(const Allocator& alloc = Allocator())
            : size_(0)
            , capacity_(10)
            , allocator_(alloc)
        {
            data_ = allocator_.allocate(capacity_);
        }

        Vector(size_t n, const T& value = T(), const Allocator& alloc = Allocator())
            : size_(n)
            , capacity_(n * 2)
            , allocator_(alloc)
        {
            data_ = allocator_.allocate(capacity_);
            for (size_t i = 0; i < size_; ++i)
            {
                allocator_.construct(data_ + i, value);
            }
        }

        Vector(std::initializer_list<T> lst, const Allocator& alloc = Allocator())
            : size_(0)
            , capacity_(size_ * 2)
            , allocator_(alloc)
        {
            data_ = allocator_.allocate(capacity_);
            for (const auto &val : lst)
            {
                push_back(val);
            }
        }

        ~Vector()
        {
            for (size_t i = 0; i < size_; ++i)
            {
                allocator_.destroy(data_ + i);
            }
            allocator_.deallocate(data_, capacity_);
        }

        void reserve(size_t n)
        {
            T* newArr = allocator_.allocate(n);
            size_t i = 0;
            iterator it = begin();
            try {
                for (; it != end(); ++it, ++i)
                {
                    allocator_.construct(newArr + i, *it);
                }
            } catch (...) {
                for (size_t j = 0; j < i; ++j)
                {
                    allocator_.destroy(newArr + j);
                }
                allocator_.deallocate(newArr, n);
            }
            for (iterator it = begin(); it != end(); ++it)
            {
                allocator_.destroy(&*it);
            }
            allocator_.deallocate(data_, capacity_);
            capacity_ = n;
            data_ = newArr;
        }

        void push_back(const T& value)
        {
            if (size_ == capacity_) reserve(2 * capacity_);
            allocator_.construct(data_ + size_, value);
            ++size_;
        }

        void pop_back()
        {
            allocator_.destroy(data_ + size_ - 1);
            --size_;
        }

        constexpr iterator begin() const noexcept
        {
            return iterator(data_);
        }

        constexpr iterator end() const noexcept
        {
            return iterator(data_ + size_);
        }

    };

} // namespace S21

#endif // VECTOR_H
