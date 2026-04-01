#pragma once
#include <cstdint>
#include <cstddef>

class Arena {
    private:
        uint8_t* base;      
        size_t   offset;    
        size_t   capacity;  
        size_t   initial_capacity;
    public:
        Arena(size_t size) {
            initial_capacity = size + sizeof(void*);
            base = nullptr; // Başlangıçta boş
            new_block(size); // İlk bloğu oluştur ve bağla
        }

        Arena(Arena&& other) {
            base     = other.base;
            offset   = other.offset;
            capacity = other.capacity;
            other.base = nullptr;
            other.offset = 0;
            other.capacity = 0;
            initial_capacity = 0;
        }
        ~Arena() {
            uint8_t* curr = base;
            while (curr != nullptr) {
                uint8_t* prev = *(uint8_t**)curr; 
                delete[] curr; 
                curr = prev;
            }
        }
        template<typename T, typename... Args>
        T* alloc_new(Args&&... args) {
            void* yer = alloc(sizeof(T),alignof(T));
            new(yer) T(args...);
            return reinterpret_cast<T*>(yer);
        }
        void new_block(size_t size) {
            uint8_t* new_memory = new uint8_t[size + sizeof(void*)];
            *(uint8_t**)new_memory = base; // Eski base'i yeni bloğun başına yaz (Zincirle)
            base = new_memory;
            offset = sizeof(void*); // 8 byte'lık header'dan sonrasına yazmaya başla
            capacity = size + sizeof(void*);
        }

        void* alloc(size_t bytes, size_t align = alignof(max_align_t)) {
            size_t aligned = (offset + align - 1) & ~(align - 1);

            if (aligned + bytes > capacity) {
                new_block(bytes > 1024 ? bytes : 1024);
                aligned = (offset + align - 1) & ~(align - 1);
            }

        void* ptr = base + aligned;              
            offset = aligned + bytes;                           
            return ptr; 
        }
        Arena(const Arena&) = delete;
        Arena& operator=(const Arena&) = delete;

        void reset() {
            uint8_t* curr = base;
        while (true) {
            uint8_t* prev = *(uint8_t**)curr;
            if (prev == nullptr) {
                base =  curr;
                offset = sizeof(void*);
                capacity = initial_capacity;
                break;
            }
            delete[] curr;
            curr = prev;
        }
        }
};
