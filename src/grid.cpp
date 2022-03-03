#include "grid.hpp"
#include "color.hpp"
#include <iostream>

using std::cout;
using std::make_pair;
using std::pair;

Grid::Grid(const int &_rows, const int &_cols) : rows(_rows), cols(_cols) {
    // TODO: assert allocation occurred normally
    this->values = new (std::nothrow) char *[this->rows];
    for (int i = 0; i < this->rows; ++i) {
        this->values[i] = new (std::nothrow) char[this->cols];
    }
}
Grid::~Grid() {
    for (int i = 0; i < this->rows; ++i)
        delete[] this->values[i];
    delete[] this->values;
}

void Grid::printHeader() const {
    cout.put('\n');
    cout << BLU << "   │ " << RESET;
    for (int i = 1; i < this->cols - 1; ++i) {
        cout << i;
        (i != this->cols - 2) ? cout << BLU << " │ " << RESET : cout.put('\n');
    }
}

void Grid::printSeparator() const {
    for (int i = 0; i < cols - 2; ++i)
        cout << BLU << "───┼" << RESET;
    cout << BLU << "───\n" << RESET;
}

void Grid::print(const std::set<std::pair<int, int>> &marked,
                 const std::set<std::pair<int, int>> &revealed) const {
    printHeader();
    char col = 'A';
    for (int i = 1; i < this->rows - 1; ++i) {
        printSeparator();
        cout << ' ' << col << BLU << " │ " << RESET;
        for (int j = 1; j < this->cols - 1; ++j) {
            const pair<int, int> p = make_pair(i, j);
            if (marked.find(p) != marked.end())
                cout << RED << this->mark << RESET;
            else if (revealed.find(p) != revealed.end()) {
                const char c = this->values[i][j];
                if (c == '0') cout << ' ';
                else cout << YEL << c << RESET;
            } else cout << GRE << hidden << RESET;
            if (j != this->cols - 2) cout << BLU << " │ " << RESET;
        }
        ++col;
        cout.put('\n');
    }
    cout.put('\n');
}

void Grid::initialize() {
    for (int i = 1; i < this->rows - 1; ++i) {
        for (int j = 1; j < this->cols - 1; ++j) {
            // The cell itself isn't counted
            if (this->values[i][j] != this->bomb) {
                this->values[i][j] = countBombs(i, j);
            }
        }
    }
}

char Grid::countBombs(const int &m, const int &n) {
    char bombNeighbors = '0';
    for (int i = m - 1; i <= m + 1; ++i) {
        for (int j = n - 1; j <= n + 1; ++j) {
            if (this->values[i][j] == this->bomb) bombNeighbors++;
        }
    }
    return bombNeighbors;
}

bool Grid::isOutOfBounds(const std::pair<int, int> &p) const {
    return (p.first <= 0 || p.first >= this->rows - 1 || p.second <= 0 ||
            p.second >= this->cols - 1);
}
