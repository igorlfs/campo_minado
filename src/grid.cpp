#include "grid.hpp"
#include "color.hpp"
#include "msgassert.hpp"

using std::make_pair;
using std::ostream;
using std::pair;
using std::set;

Grid::Grid(const int &_rows, const int &_cols, ostream &_ostream)
    : rows(_rows), cols(_cols), outStream(_ostream) {

    assert(this->rows > 0, "Number of rows needs to be a positive integer");
    assert(this->cols > 0, "Number of columns needs to be a positive integer");

    this->values.resize(this->rows);
    for (int i = 0; i < this->rows; ++i) {
        this->values.at(i).resize(this->cols);
    }
}

void Grid::printHeader() const {
    this->outStream.put('\n');
    this->outStream << BLU << "   │ " << RESET;
    for (int i = 1; i < this->cols - 1; ++i) {
        this->outStream << i;
        (i != this->cols - 2) ? this->outStream << BLU << " │ " << RESET
                              : this->outStream.put('\n');
    }
}

void Grid::printSeparator() const {
    for (int i = 0; i < cols - 2; ++i) {
        this->outStream << BLU << "───┼" << RESET;
    }
    this->outStream << BLU << "───\n" << RESET;
}

void Grid::print(const set<pair<int, int>> &marked,
                 const set<pair<int, int>> &revealed) const {
    printHeader();
    char col = 'A';

    for (int i = 1; i < this->rows - 1; ++i) {
        printSeparator();
        this->outStream << ' ' << col << BLU << " │ " << RESET;

        for (int j = 1; j < this->cols - 1; ++j) {
            const pair<int, int> P = make_pair(i, j);

            if (marked.contains(P)) {
                this->outStream << RED << MARK << RESET;
            } else if (revealed.contains(P)) {
                switch (this->values.at(i).at(j)) {
                case NOT:
                    this->outStream << BLANK;
                    break;
                case BOMB:
                    this->outStream << MAG << BOMB << RESET;
                    break;
                default:
                    this->outStream << YEL << this->values.at(i).at(j) << RESET;
                }
            } else {
                this->outStream << GRE << HIDDEN << RESET;
            }
            if (j != this->cols - 2) {
                this->outStream << BLU << " │ " << RESET;
            }
        }
        ++col;
        this->outStream.put('\n');
    }
    this->outStream.put('\n');
}

void Grid::initialize() {
    for (int i = 1; i < this->rows - 1; ++i) {
        for (int j = 1; j < this->cols - 1; ++j) {
            if (this->values.at(i).at(j) != BOMB) {
                this->values.at(i).at(j) = countBombs(i, j);
            }
        }
    }
}

char Grid::countBombs(const int &m, const int &n) {
    char bombNeighbors = NOT;
    for (int i = m - 1; i <= m + 1; ++i) {
        for (int j = n - 1; j <= n + 1; ++j) {
            if (this->values.at(i).at(j) == BOMB) {
                bombNeighbors++;
            }
        }
    }
    return bombNeighbors;
}

bool Grid::isOutOfBounds(const pair<int, int> &pos) const {
    return (pos.first <= 0 || pos.first >= this->rows - 1 || pos.second <= 0 ||
            pos.second >= this->cols - 1);
}
