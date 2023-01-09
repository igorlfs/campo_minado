#pragma once

#include <iostream>
#include <utility>

using std::cout;
using std::istream;
using std::ostream;
using std::pair;

class Input {
  public:
    static void greetAction(ostream &outStream = cout);
    static char getAction(istream &inStream, ostream &outStream);
    static void greetPosition(ostream &outStream = cout);
    static pair<int, int> getPosition(istream &inStream, ostream &outStream);
};
