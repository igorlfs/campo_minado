#pragma once

#include "grid.hpp"
#include <set>
#include <utility>

class Logic {
  public:
    Logic(const int &_numBombs) : numBombs(_numBombs) {}

    void setAction(const char &c) { this->action = c; }

    bool hasWon(const Grid &g) const;

    void placeBombs(Grid &g);
    void update(const Grid &g, const std::pair<int, int> &p);
    void handleReveal(const std::pair<int, int> &p, const Grid &g);
    void reveal(const std::pair<int, int> &p, const Grid &g);
    void handleMark(const std::pair<int, int> &p);
    void handleUndo(const std::pair<int, int> &p);

  private:
    int numBombs;
    char action;
    std::set<std::pair<int, int>> revealed;
    std::set<std::pair<int, int>> marked;
    std::set<std::pair<int, int>> bombs;

    friend class Mines;
};

struct exploded {};
struct repeated {};
struct unmarkable {};
struct notmarked {};
