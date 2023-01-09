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

using std::pair;

class Grid {

  public:
    Grid(const int &_rows, const int &_cols, std::ostream &_ostream);

    [[nodiscard]] int getRows() const { return this->rows; }
    [[nodiscard]] int getCols() const { return this->cols; }
    [[nodiscard]] char getValue(const pair<int, int> &pos) const {
        return this->values.at(pos.first).at(pos.second);
    }
    [[nodiscard]] unsigned getSize() const {
        return (this->rows - 2) * (this->cols - 2);
    }

    void placeBomb(const pair<int, int> &pos) {
        this->values.at(pos.first).at(pos.second) = BOMB;
    }

    void printHeader() const;
    void printSeparator() const;
    void print(const std::set<pair<int, int>> &marked,
               const std::set<pair<int, int>> &revealed) const;

    void initialize();
    char countBombs(const int &m, const int &n);

    [[nodiscard]] bool isOutOfBounds(const pair<int, int> &pos) const;

  private:
    int rows;
    int cols;
    std::vector<std::vector<char>> values;
    std::ostream &outStream;
};
