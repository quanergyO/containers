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
    S21::Vector<int> s(1);
    for (size_t i = 0; i < 100; ++i)
    {
        s.push_back(i);
    }
    for (auto x : s)
        std::cout << x << ' ';

    return 0;
}
