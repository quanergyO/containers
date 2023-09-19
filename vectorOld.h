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
    T* arr_;
    size_t size_;
    size_t capacity_;
    Allocator allocator_;

    using value_type = T;
    using allocator_type = Allocator;
    using size_type = unsigned int;

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
        arr_ = allocator_.Allocate(capacity_);
        for (size_t i = 0; i < size_; ++i)
        {
            allocator_.Construct(&arr_[i]);
        }
    }

    Vector(size_t n, const T& value = T(), const Allocator& alloc = Allocator())
        : size_(n)
        , capacity_(n * 2)
        , allocator_(alloc)
    {
        arr_ = allocator_.Allocate(capacity_);
        for (size_t i = 0; i < size_; ++i)
        {
            allocator_.Construct(&arr_[i], value);
        }
    }

    ~Vector()
    {
        for (size_t i = 0; i < size_; ++i)
        {
            allocator_.Destroy(&arr_[i]);
        }
        allocator_.Deallocate(arr_, capacity_);
    }

    template <bool IsConst>
    CommonIterator<IsConst> begin() const noexcept
    {
        //TODO where?
    }

};

} // namespace S21
