# Arena Allocator (C++)

## Ne yapar

Tek bir veya birden fazla büyük bellek bloğu üzerinden, pointer kaydırarak O(1) maliyetle allocation yapan basit bir arena allocator.

## What it does

A simple arena allocator that performs O(1) allocations by advancing a pointer over one or more large memory blocks.

---

## Neden

Standart `new` / `malloc`:

* sık allocation’da maliyetli
* fragmentation oluşturabilir
* deterministik değildir

Arena allocator:

* tek seferde blok alır
* allocation = pointer arithmetic
* reset ile toplu temizleme

## Why

Standard `new` / `malloc`:

* costly under frequent allocations
* may introduce fragmentation
* non-deterministic behavior

Arena allocator:

* allocates large blocks once
* allocation is just pointer arithmetic
* supports bulk reset instead of individual frees

---

## Özellikler

* **Alignment desteği**
  `alignof(T)` ile uyumlu hizalama yapılır.

* **Otomatik büyüme**
  Mevcut blok dolunca yeni blok eklenir (linked-list yapı).

* **Move semantics**
  Ownership taşınabilir.

* **Placement new desteği**
  Obje doğrudan arena içinde oluşturulabilir.

* **O(1) reset**
  Tüm allocation’lar tek adımda geçersiz hale getirilir.

## Features

* **Alignment support**
  Allocations respect `alignof(T)` requirements.

* **Automatic growth**
  Allocates new blocks when the current one is full (linked-list structure).

* **Move semantics**
  Ownership can be transferred safely.

* **Placement new support**
  Objects can be constructed directly inside the arena.

* **O(1) reset**
  All allocations can be invalidated in constant time.

---

## Kullanım

```cpp
Arena arena(1024);

// raw allocation
void* mem = arena.alloc(64);

// object allocation
int* x = arena.alloc_new<int>(42);

// reset
arena.reset();
```

## Usage

```cpp
Arena arena(1024);

// raw allocation
void* mem = arena.alloc(64);

// object allocation
int* x = arena.alloc_new<int>(42);

// reset
arena.reset();
```

---

## Benchmark

Senaryo:

* çok sayıda küçük allocation

Sonuç:

* malloc: 0.005986 saniye
* arena:  0.00194 saniye
* fark:   **3.08x daha hızlı**

## Benchmark

Scenario:

* large number of small allocations

Results:

* malloc: 0.005986 seconds
* arena:  0.00194 seconds
* difference: **3.08x faster**

---

## Nasıl çalışır

* Her blok başında bir pointer tutulur (önceki bloğa işaret eder)
* Allocation:

  * offset hizalanır
  * pointer döndürülür
  * offset ilerletilir
* Blok dolarsa:

  * yeni blok allocate edilir
  * zincire eklenir

## How it works

* Each block stores a pointer to the previous block
* Allocation:

  * offset is aligned
  * pointer is returned
  * offset is advanced
* When a block is full:

  * a new block is allocated
  * linked into the chain

---

## Sınırlamalar

* `free` yoktur
* destructor’lar otomatik çağrılmaz
* sadece ileri doğru allocation yapılır

## Limitations

* no individual `free`
* destructors are not automatically called
* allocation is strictly linear

---

## Kullanım alanları

* oyun motorları
* geçici veri yapıları
* performans kritik sistemler

## Use cases

* game engines
* transient data structures
* performance-critical systems
=======
# Arena-allocator
>>>>>>> cb65d85c55c16f50011d4172fbe9e69e74bd5595
