#pragma once

#include "grid.hpp"
#include <iostream>
#include <set>
#include <utility>

class Logic {
  public:
    Logic(const int &_numBombs, std::ostream &_ostream)
        : numBombs(_numBombs), outStream(_ostream) {}

    [[nodiscard]] bool hasWon(const int &gridSize) const;
    [[nodiscard]] bool hasExploded() const { return this->exploded; }

    void placeBombs(Grid &g);

    void handleMark(const std::pair<int, int> &p);
    void handleUnmark(const std::pair<int, int> &p) { this->marked.erase(p); };
    void handleReveal(const std::pair<int, int> &p, const Grid &g);

  private:
    bool exploded{false};
    int numBombs;
    char action;
    std::ostream &outStream;
    std::set<std::pair<int, int>> revealed;
    std::set<std::pair<int, int>> marked;
    std::set<std::pair<int, int>> bombs;

    void reveal(const std::pair<int, int> &p, const Grid &g);

    friend class Mines;
};

struct exploded {};
struct repeated {};
struct unmarkable {};
struct notmarked {};
