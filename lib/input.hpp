#pragma once

#include <utility>

class Input {
  public:
    static void greetAction();
    static char getAction();
    static void greetPosition();
    static std::pair<int, int> getPosition();
};

struct interrupt {};
struct invalidAction {};
struct invalidActionFormat {};
struct invalidPositionFormat {};
