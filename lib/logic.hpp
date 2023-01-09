#pragma once

#include "grid.hpp"
#include <iostream>
#include <set>
#include <utility>

using std::ostream;
using std::pair;
using std::set;

class Logic {
  public:
    Logic(const int &_numBombs, ostream &_ostream)
        : numBombs(_numBombs), outStream(_ostream) {}

    [[nodiscard]] bool hasWon(const int &gridSize) const;
    [[nodiscard]] bool hasExploded() const { return this->exploded; }

    void placeBombs(Grid &grid);

    void handleMark(const pair<int, int> &loc);
    void handleUnmark(const pair<int, int> &pos) { this->marked.erase(pos); };
    void handleReveal(const pair<int, int> &pos, const Grid &grid);

  private:
    bool exploded{false};
    int numBombs;
    char action;
    ostream &outStream;
    set<pair<int, int>> revealed;
    set<pair<int, int>> marked;
    set<pair<int, int>> bombs;

    void reveal(const pair<int, int> &pos, const Grid &grid);

    friend class Mines;
};
