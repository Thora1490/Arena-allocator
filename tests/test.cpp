#include "arena.hpp"
#include <iostream>

int main() {
    Arena a(1024);
    void *x = a.alloc(8, 8);   
    void* y = a.alloc(32, 8);  

    std::cout << x << "\n";
    std::cout << y << "\n";

    a.reset();

    void* z = a.alloc(8, 8);
    std::cout << z << "\n";

    struct Roket {
        float hiz;
        float irtifa;
        Roket(float h, float i) : hiz(h), irtifa(i) {}
    };

    Roket* r = a.alloc_new<Roket>(340.0f, 1000.0f);
    std::cout << r->hiz << "\n";
    std::cout << r->irtifa << "\n";
    return 0;
}