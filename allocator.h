#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>

template <typename T>
class Allocator
{
public:

    [[ nodiscard ]] T* allocate(size_t n)
    {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void deallocate(T* ptr, size_t n)
    {
        ::operator delete(ptr);
    }

    template<typename U, typename ... Args>
    void construct(U* ptr, Args&&... args)
    {
        new(static_cast<void*>(ptr)) T(std::forward<Args>(args)...);
    }

    void destroy(T* ptr)
    {
        ptr->~T();
    }
};

#endif // ALLOCATOR_H
