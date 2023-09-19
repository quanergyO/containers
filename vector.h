#include <iostream>
#include "allocator.h"

template <typename T, typename Allocator = Allocator<T>>
class Vector
{
private:
    T* arr_;
    size_t size_;
    size_t capacity_;
    Allocator allocator_;

    using value_type = T;
    using allocator_type = Allocator;
    using size_type = unsigned int;
    using reference = value_type&;
    using const_reference = const value_type&;

public:
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
        std::cout << "Destroy Vector\n";
    }

};
