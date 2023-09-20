#include <iostream>
#include "allocator.h"
#include "conditional.h"

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

        using value_type = T;
        using allocator_type = Allocator;
        using size_type = size_t;

    public:
        template <bool IsConst>
        struct CommonIterator
        {
        private:
            using iterator = CommonIterator<false>;
            using const_iterator = CommonIterator<true>;
            using ConditionalValueType = conditional_t<IsConst, const T, T>;
            using ConditionalPtr = conditional_t<IsConst, const T*, T*>;
            using ConditionalReference = conditional_t<IsConst, const T&, T&>;

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

        explicit Vector(const Allocator& alloc = Allocator())
            : size_(0)
            , capacity_(10)
            , allocator_(alloc)
        {
            data_ = allocator_.Allocate(capacity_);
            for (size_t i = 0; i < size_; ++i)
            {
                allocator_.Construct(data + i);
            }
        }

        Vector(size_t n, const T& value = T(), const Allocator& alloc = Allocator())
            : size_(n)
            , capacity_(n * 2)
            , allocator_(alloc)
        {
            data_ = allocator_.Allocate(capacity_);
            for (size_t i = 0; i < size_; ++i)
            {
                allocator_.Construct(data + i, value);
            }
        }

        ~Vector()
        {
            for (size_t i = 0; i < size_; ++i)
            {
                allocator_.Destroy(data + i);
            }
            allocator_.Deallocate(data_, capacity_);
        }

        void reserve(size_t n)
        {
            T* newArr = allocator_.Allocate(n);
            size_t i = 0;
            try {
                for (; i < size_; ++i)
                {
                    allocator_.Construct(newArr + i, data + i));
                }
            }
            catch (...) {
                for (size_t j = 0; j < i; ++j)
                {
                    allocator_.Destroy(newArr + j);
                }
                allocator_.Deallocate(newArr, n);
            }
            for (size_t i = 0; i < size_; ++i)
            {
                allocator_.Destroy(data_ + i);
            }
            allocator._Deallocate(data_);
            capacity_ = n;
            data_ = newArr
        }

        void push_back(const T& value)
        {
            if (size_ == capacity_) reserve(2 * capacity_);
            allocator_.Construct(data_ + size_, value);
            ++size_
        }

        void pop_back()
        {
            allocator_.Destroy(data_ + size_ - 1);
            --size_;
        }


        template <bool IsConst>
        CommonIterator<IsConst> begin() const noexcept
        {
            return CommonIterator<false>(data_);
        }

    };

} // namespace S21
