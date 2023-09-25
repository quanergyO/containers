#include <iostream>

int main() {
    int a = 10;
    int b = 20;
    const int * p_a = &a;
    int * const p_b = &b;
    *p_a = 33;
    *p_b = 33;
    p_a = &b;
    p_b = &a;


    return 0;
}
