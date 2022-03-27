#pragma once

#include <iostream>
#include <utility>

class Input {
  public:
    static void greetAction(std::ostream &outStream = std::cout);
    static char getAction(std::istream &inStream, std::ostream &outStream);
    static void greetPosition(std::ostream &outStream = std::cout);
    static std::pair<int, int> getPosition(std::istream &inStream,
                                           std::ostream &outStream);
};
