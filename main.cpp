#include "vector.h"
#include <array>
#include <iostream>

struct S {
    int a;
    S() : a(1) { std::cout << "S created\n"; }
    S(const S& obj) : a(obj.a) { std::cout << "S copyed\n"; }
    ~S() { std::cout << "S deleted\n"; }
};

int main()
{
    std::array<S, 10> s;

    return 0;
}
