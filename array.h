#ifndef ARRAY_H
#define ARRAY_H

#include <cstddef>

template <typename T, std::size_t N>
struct Array
{
    using value_type = T;
    using size_type = std::size_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = value_type*;
    using cosnt_pointer = const value_type*;

    reference At(size_t index)
    {

    }

private:
    value_type arr_[N];
};

#endif // ARRAY_H
