#include <iostream>
#include "vectorOld.h"

struct S {
    int a;
    S() : a(1) { std::cout << "S created\n"; }
    S(const S& obj) : a(obj.a) { std::cout << "S copyed\n"; }
    ~S() { std::cout << "S deleted\n"; }
};

int main()
{
    S21::Vector<int> s(5);

    return 0;
}
