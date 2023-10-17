#ifndef CPP2_S21_CONTAINERS_1_UTILS_ALLOCATOR_H_
#define CPP2_S21_CONTAINERS_1_UTILS_ALLOCATOR_H_

#include <iostream>

template <typename T>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using const_pointer = const T*;
    using reference = T&;
    using const_reference = const T&;
    using size_type = size_t;
    using difference_type = ptrdiff_t;

    [[nodiscard]] static pointer allocate(size_t n)
    {
        return static_cast<pointer>(::operator new(n * sizeof(value_type)));
    }

    static void deallocate(pointer ptr, size_type)
    {
        ::operator delete(ptr);
    }

    template <typename U, typename... Args>
    static void construct(U *ptr, Args &&...args)
    {
        new (static_cast<void *>(ptr)) T(std::forward<Args>(args)...);
    }

    static void destroy(pointer ptr)
    {
        ptr->~T();
    }
    
    template< class U  >
    struct rebind_alloc
    {
        using other = Allocator<U>;
    };
    
};

#endif // CPP2_S21_CONTAINERS_1_UTILS_ALLOCATOR_H_
