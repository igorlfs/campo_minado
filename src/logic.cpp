#include "logic.hpp"
#include "actions.hpp"
#include "random.hpp"

using std::make_pair;
using std::pair;

bool Logic::hasWon(const int &gridSize) const {
    const bool MARKS = this->marked == this->bombs;
    const bool REVEALS = this->revealed.size() == gridSize - this->bombs.size();
    return (MARKS && REVEALS);
}

void Logic::placeBombs(Grid &grid) {
    for (int i = 0; i < this->numBombs; ++i) {
        while (true) {
            pair<int, int> bomb = make_pair(Random::rng(1, grid.getRows() - 2),
                                            Random::rng(1, grid.getCols() - 2));
            if (!this->bombs.contains(bomb)) {
                grid.placeBomb(bomb);
                this->bombs.insert(bomb);
                break;
            }
        }
    }
}

void Logic::handleMark(const pair<int, int> &loc) {
    if (this->revealed.contains(loc)) {
        this->outStream << "\nVocê não pode marcar uma posição revelada.\n\n";
    } else {
        this->marked.insert(loc);
    }
}

void Logic::handleReveal(const pair<int, int> &pos, const Grid &grid) {
    if (this->bombs.contains(pos)) {
        // Reveal bomb to print it after exploding
        this->revealed.insert(pos);
        // It may also be necessary to erase the bomb from marked
        this->marked.erase(pos);
        this->exploded = true;
    } else {
        reveal(pos, grid);
    }
}

void Logic::reveal(const pair<int, int> &pos, const Grid &grid) {
    // Boundary check
    if (grid.isOutOfBounds(pos)) {
        return;
    }

    // Reveal
    this->revealed.insert(pos);

    // Remove marked position if necessary
    if (this->marked.contains(pos)) {
        this->marked.erase(pos);
    }

    // Stop searching when a non null number is found;
    // Note that while searching, it's impossible to find a bomb:
    // we check separately if a bomb was selected at first, which leaves 2
    // options: either zero hasn't been chosen, which stops the search
    // immediately OR the number is zero, but a bomb can only be surrounded by
    // non null numbers and the search stops when finding them.
    if (grid.getValue(pos) != NOT) {
        return;
    }

    // Recursively search the surroundings if they haven't been searched yet
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            const pair<int, int> Q = make_pair(pos.first + i, pos.second + j);
            if (!this->revealed.contains(Q)) {
                reveal(Q, grid);
            }
        }
    }
}
