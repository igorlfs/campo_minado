#pragma once

#include "grid.hpp"
#include "logic.hpp"
#include <utility>

class Mines {
  public:
    Mines(const int &_rows, const int &_cols, const int &_bombs);

    [[nodiscard]] bool isGameOver() const { return this->gameOver; }

    void getInput();
    void update();
    void print() const;

  private:
    std::pair<int, int> position{0, 0};
    bool gameOver{false};
    Grid grid;
    Logic engine;
};
