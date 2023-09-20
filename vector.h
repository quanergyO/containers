#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <limits>
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
        size_t size_;
        size_t capacity_;
        Allocator allocator_;
        T* data_;

    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using allocator_type = Allocator;
        using iterator = RandomAccessIterator<T>;
        using const_iterator = RandomAccessIterator<const T*>;

        using size_type = size_t;

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
            , capacity_(lst.size() * 2)
            , allocator_(alloc)
        {
            data_ = allocator_.allocate(capacity_);
            for (const auto &value : lst)
            {
                push_back(value);
            }
        }

        Vector(const Vector<T> &item)
            : size_(item.size_)
            , capacity_(item.capacity_)
            , allocator_(item.allocator_)
        {
            data_ = allocator_.allocate(capacity_);
            for (const auto &value : item)
            {
                push_back(value);
            }
        }

        Vector(Vector<T> &&item) noexcept
            : size_(item.size_)
            , capacity_(item.capacity_)
            , allocator_(item.allocator_)
            , data_(item.data_)
        {
            item.data_ = nullptr;
            size_ = 0;
            capacity_ = 0;
        }

        Vector<T>& operator=(Vector<T> &&rhs) noexcept
        {
            if (this == &rhs) return this;
            for (auto &it : *this)
            {
                allocator_.destroy(&it);
            }
            allocator_.deallocate(data_, capacity_);
            data_ = rhs.data_;
            size_ = rhs.size_;
            capacity_ = rhs.capacity_;
            allocator_ = rhs.allocator_;
            rhs.data_ = nullptr;
            rhs.size_ = 0;
            rhs.capacity_ = 0;
            return *this;
        }

        ~Vector()
        {
            for (auto &it : *this)
            {
                allocator_.destroy(&it);
            }
            allocator_.deallocate(data_, capacity_);
        }

        reference at(size_type pos) const
        {
            if (pos > size_) throw std::invalid_argument("Index out of range");
            return *(data_ + pos);
        }

        reference operator[](size_type pos)
        {
            return *(data_ + pos);
        }

        const_reference front() const noexcept
        {
            return data_[0];
        }

        const_reference back() const noexcept
        {
            return data_[size_ - 1];
        }

        T* data() const noexcept
        {
            return data_;
        }

        constexpr iterator begin() const noexcept
        {
            return iterator(data_);
        }

        constexpr iterator end() const noexcept
        {
            return iterator(data_ + size_);
        }

        bool empty() const noexcept
        {
            return size_ == 0;
        }

        size_type size() const noexcept
        {
            return size_;
        }

        size_type max_size() const noexcept
        {
            return std::numeric_limits<T>::max();
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
            for (auto &it : *this)
            {
                allocator_.destroy(&it);
            }
            allocator_.deallocate(data_, capacity_);
            capacity_ = n;
            data_ = newArr;
        }

        size_type capacity() const noexcept
        {
            return capacity_;
        }

        void shrink_to_fit()
        {

        }

        void clear() noexcept
        {
            for (auto &it : *this)
            {
                allocator_.destroy(&it);
            }
            size_ = 0;
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

    };

} // namespace S21

#endif // VECTOR_H
