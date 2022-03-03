#pragma once

#include <set>
#include <utility>

class Grid {
    static constexpr char bomb = 'b';
    static constexpr char mark = 'm';
    static constexpr char hidden = '+';

  public:
    Grid(const int &_rows, const int &_cols);
    ~Grid();

    char getValue(const std::pair<int, int> &p) const {
        return this->values[p.first][p.second];
    }
    unsigned size() const { return (this->rows - 2) * (this->cols - 2); }

    void placeBomb(const std::pair<int, int> &p) {
        this->values[p.first][p.second] = this->bomb;
    }

    int getRows() const { return this->rows; }
    int getCols() const { return this->cols; }

    void printHeader() const;
    void printSeparator() const;
    void print(const std::set<std::pair<int, int>> &marked,
               const std::set<std::pair<int, int>> &revealed) const;

    void initialize();
    char countBombs(const int &m, const int &n);

    bool isOutOfBounds(const std::pair<int, int> &p) const;

  private:
    int rows;
    int cols;
    char **values;
};
