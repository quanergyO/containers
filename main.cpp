#include <iostream>
#include "vector.h"

struct S {
    int a;
    S() : a(1) { std::cout << "S created\n"; }
    S(const S& obj) : a(obj.a) { std::cout << "S copyed\n"; }
    ~S() { std::cout << "S deleted\n"; }
};

int main()
{
    S21::Vector<int> v;
    std::cout << "Default-constructed capacity is " << v.capacity() << '\n';
    for (size_t i = 0; i < 100; ++i)
    {
        v.push_back(i);
    }
    std::cout << "Capacity of a 100-element vector is " << v.capacity() << '\n';
    v.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';
    v.clear();
    std::cout << "Capacity after clear() is " << v.capacity() << '\n';
    v.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';
    for (int i = 1000; i < 1300; ++i)
        v.push_back(i);
    std::cout << "Capacity after adding 300 elements is " << v.capacity() << '\n';
    v.shrink_to_fit();
    std::cout << "Capacity after shrink_to_fit() is " << v.capacity() << '\n';

    return 0;
}
