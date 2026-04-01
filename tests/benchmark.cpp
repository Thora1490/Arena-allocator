#include "arena.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>

int main() {
    const int TEKRAR = 1000000;

    // --- malloc testi ---
    volatile void* son = nullptr;
    clock_t baslangic = clock();
    for (int i = 0; i < TEKRAR; i++) {
        void* ptr = malloc(64);
        son = ptr;
        free(ptr);
    }
    clock_t bitis = clock();
    double malloc_sure = (double)(bitis - baslangic) / CLOCKS_PER_SEC;

    // --- Arena testi ---
    Arena a(64 * TEKRAR);
    baslangic = clock();
    for (int i = 0; i < TEKRAR; i++) {
        son = a.alloc(64,8);
    }
    bitis = clock();
    double arena_sure = (double)(bitis - baslangic) / CLOCKS_PER_SEC;

    std::cout << "malloc: " << malloc_sure << " saniye\n";
    std::cout << "arena:  " << arena_sure  << " saniye\n";
    std::cout << "fark:   " << malloc_sure / arena_sure << "x\n";

    return 0;
}