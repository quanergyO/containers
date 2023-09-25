#include <iostream>
#include "vector.h"

int main() {
    s21::vector<int> v {1, 2, 3, 4, 5};
    v.push_back(10);
    v.pop_back();
    v.pop_back();
    const s21::vector<int> b {5, 4, 3, 2, 1};
    for (auto &x : b)
        x = 11;
    for (auto &x : b)
        std::cout << x << ' ';
    return 0;
}
