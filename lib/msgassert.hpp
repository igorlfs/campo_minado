#pragma once

#include <iostream>

#ifndef NDEBUG
#define assert(Expr, Msg) __assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#define assertUser(Expr, Msg) __assertUser(Expr, Msg)
#else
#define assert(Expr, Msg)
#define assertUser(Expr, Msg)
#endif

// @brief Displays a helpful message to aid debugging
inline void __assert(const char *expr_str, const bool &expr, const char *file,
                     const int &line, const char *msg) {
    if (!expr) {
        std::cerr << "Assert failed:\t" << msg << "\n"
                  << "Expected:\t" << expr_str << "\n"
                  << "Source:\t\t" << file << ", line " << line << "\n";
        abort();
    }
}

// @brief Displays a friendly message to the user and aborts
inline void __assertUser(const bool &expr, const char *msg) {
    if (!expr) {
        std::cerr << "\n" << msg << "\n";
        abort();
    }
}
