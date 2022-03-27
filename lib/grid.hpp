#pragma once

#include <iostream>
#include <set>
#include <utility>
#include <vector>

static constexpr char BOMB = 'b';
static constexpr char MARK = 'm';
static constexpr char HIDDEN = '+';
static constexpr char BLANK = ' ';
static constexpr char NOT = '0';

class Grid {

  public:
    Grid(const int &_rows, const int &_cols, std::ostream &_ostream);

    [[nodiscard]] int getRows() const { return this->rows; }
    [[nodiscard]] int getCols() const { return this->cols; }
    [[nodiscard]] char getValue(const std::pair<int, int> &p) const {
        return this->values.at(p.first).at(p.second);
    }
    [[nodiscard]] unsigned getSize() const {
        return (this->rows - 2) * (this->cols - 2);
    }

    void placeBomb(const std::pair<int, int> &p) {
        this->values.at(p.first).at(p.second) = BOMB;
    }

    void printHeader() const;
    void printSeparator() const;
    void print(const std::set<std::pair<int, int>> &marked,
               const std::set<std::pair<int, int>> &revealed) const;

    void initialize();
    char countBombs(const int &m, const int &n);

    [[nodiscard]] bool isOutOfBounds(const std::pair<int, int> &p) const;

  private:
    int rows;
    int cols;
    std::vector<std::vector<char>> values;
    std::ostream &outStream;
};
