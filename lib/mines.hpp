#pragma once

#include "grid.hpp"
#include "logic.hpp"
#include <utility>

class Mines {
  public:
    Mines(const int &_rows, const int &_cols, const int &_bombs);

    // Getters
    [[nodiscard]] bool isGameOver() const { return this->gameOver; }

    void input();
    void update();
    void print() const;

  private:
    std::pair<int, int> pos{0, 0};
    bool gameOver{false};
    char action{0};
    Grid grid;
    Logic logic;
};
