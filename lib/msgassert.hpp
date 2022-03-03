#pragma once

#include <iostream>

#ifndef NDEBUG
#define assert(Expr, Msg) __assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#define assert(Expr, Msg) ;
#endif

inline void __assert(const char *expr_str, const bool &expr, const char *file,
                     const int &line, const char *msg) {
    if (!expr) {
        std::cerr << "Assert failed:\t" << msg << "\n"
                  << "Expected:\t" << expr_str << "\n"
                  << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}
