#pragma once

// This file contains various techniques used for obfuscation and encryption,
// written by knoppi1707. If you need any help or support, please visit my website: https://ax-services.net
//
// The encryption method defined here uses a compile-time XOR-based encryption template 
// for strings. Additionally, the file includes examples of creating memory allocations,
// nested structures, and threads, as well as a Fibonacci calculation to introduce
// computational overhead. These techniques can serve as anti-analysis or obfuscation 
// mechanisms to make reverse engineering more challenging.
//
// The provided methods, such as `AllocateMemory`, `CreateNestedStructure`, and `StartThreads`,
// are designed to simulate complex behavior and resource usage, potentially misleading
// analysis tools or adding noise in debugging environments.

#include "includes.h"

using namespace std;

volatile int __fv1 = 12345, __fv2 = 67890;
constexpr char __dd[1024 * 1024] = { 0xAA };
vector<char> __dyn(1024 * 1024 * 5, 0xBB);

template <size_t __n>
struct __E {
    array<char, __n> __d;

    constexpr __E(const char(&__i)[__n], char __k = 0xAC) : __d{} {
        for (size_t __x = 0; __x < __n - 1; ++__x) {
            __d[__x] = __i[__x] ^ __k;
        }
        __d[__n - 1] = '\0';
    }

    string __dc(char __k = 0xAC) const {
        string __r;
        __r.resize(__n - 1);
        for (size_t __x = 0; __x < __n - 1; ++__x) {
            __r[__x] = __d[__x] ^ __k;
        }
        return __r;
    }
};

template <size_t __n>
constexpr auto __nx(const char(&__i)[__n]) {
    return __E<__n>(__i);
}

struct __LS {
    array<char, 1024 * 1024> __d;
};

void __Alloc() {
    volatile char* __p = new char[1024 * 1024 * 20];
    (void)__p;
}

struct __NS {
    char __d[1024 * 1024];
    __NS* __n;
};

void __Nested() {
    __NS* __h = new __NS();
    __NS* __c = __h;
    for (int __i = 0; __i < 10; ++__i) {
        __c->__n = new __NS();
        __c = __c->__n;
    }
}

void __RndFill() {
    srand(static_cast<unsigned>(time(nullptr)));
    volatile char* __rd = new char[1024 * 1024 * 5];
    for (int __i = 0; __i < 1024 * 1024 * 5; ++__i) {
        __rd[__i] = rand() % 256;
    }
}

int __Fib(int __n) {
    return (__n <= 1) ? __n : (__Fib(__n - 1) + __Fib(__n - 2));
}

void __CompFib() {
    volatile int __res = __Fib(35);
    (void)__res;
}

void __ThreadFunc() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}

void __StartTh() {
    vector<thread> __threads;
    for (int __i = 0; __i < 10; ++__i) {
        __threads.emplace_back(__ThreadFunc);
    }
    for (auto& __t : __threads) {
        __t.detach();
    }
}

void __DbgSym() {
    volatile int __x = __fv1 + __fv2;
    (void)__x;
}

atomic<int> __fc{ 0 };
map<int, string> __m;
set<int> __s;
mutex __mu;

void __MapSet() {
    lock_guard<mutex> __lk(__mu);
    for (int __i = 0; __i < 1000; ++__i) {
        __m[__i] = "R_" + to_string(__i);
        __s.insert(__i * 2);
    }
}

void __FakeCalc() {
    volatile double __r = 0.0;
    for (int __i = 0; __i < 1'000'000; ++__i) {
        __r += sin(__i) * cos(__i);
    }
    (void)__r;
}

void __AtomicOps() {
    for (int __i = 0; __i < 1000; ++__i) {
        __fc.fetch_add(1, memory_order_relaxed);
        __fc.fetch_sub(1, memory_order_relaxed);
    }
}

void __RandVec() {
    vector<int> __v(10'000'000);
    srand(static_cast<unsigned>(time(nullptr)));
    for (auto& __x : __v) {
        __x = rand() % 10'000;
    }
}

void __SimNet() {
    this_thread::sleep_for(chrono::milliseconds(500 + rand() % 1000));
}

void __GenPrimes() {
    vector<int> __p;
    for (int __i = 2; __i < 10'000; ++__i) {
        bool __isP = true;
        for (int __j = 2; __j <= sqrt(__i); ++__j) {
            if (__i % __j == 0) {
                __isP = false;
                break;
            }
        }
        if (__isP) __p.push_back(__i);
    }
}

void __Inflate() {
    volatile char __s[1024 * 1024] = { 0 };
    (void)__s;
}

void __ThrowEx() {
    try {
        throw runtime_error("EX");
    }
    catch (...) {}
}

void __FragAlloc() {
    vector<char*> __f;
    for (int __i = 0; __i < 100; ++__i) {
        __f.push_back(new char[1024 * 1024]);
        if (__i % 3 == 0) delete __f.back();
    }
    for (auto __p : __f) delete __p;
}

void __InfLoop() {
    while (true) {
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}
