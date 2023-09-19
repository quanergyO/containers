#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <iostream>

template <typename T>
class Allocator
{
public:
    T* Allocate(size_t n)
    {
        return static_cast<T*>(::operator new(n * sizeof(T)));
    }

    void Deallocate(T* ptr, size_t n)
    {
        ::operator delete(ptr);
    }

    template<typename ... Args>
    void Construct(T* ptr, const Args&... args)
    {
        new (ptr) T(args...);
    }

    void Destroy(T* ptr)
    {
        ptr->~T();
    }
};

#endif // ALLOCATOR_H
