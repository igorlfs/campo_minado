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

void Logic::placeBombs(Grid &g) {
    for (int i = 0; i < this->numBombs; ++i) {
        while (true) {
            pair<int, int> p = make_pair(Random::rng(1, g.getRows() - 2),
                                         Random::rng(1, g.getCols() - 2));
            if (this->bombs.count(p) == 0) {
                g.placeBomb(p);
                this->bombs.insert(p);
                break;
            }
        }
    }
}

void Logic::handleMark(const pair<int, int> &p) {
    if (this->revealed.count(p) > 0) {
        this->outStream << "\nVocê não pode marcar uma posição revelada.\n\n";
    } else {
        this->marked.insert(p);
    }
}

void Logic::handleReveal(const std::pair<int, int> &p, const Grid &g) {
    if (this->bombs.count(p) > 0) {
        // Reveal bomb to print it after exploding
        this->revealed.insert(p);
        // It may also be necessary to erase the bomb from marked
        this->marked.erase(p);
        this->exploded = true;
    } else {
        reveal(p, g);
    }
}

void Logic::reveal(const pair<int, int> &p, const Grid &g) {
    // Boundary check
    if (g.isOutOfBounds(p)) {
        return;
    }

    // Reveal
    this->revealed.insert(p);

    // Remove marked position if necessary
    if (this->marked.count(p) > 0) {
        this->marked.erase(p);
    }

    // Stop searching when a non null number is found;
    // Note that while searching, it's impossible to find a bomb:
    // we check separately if a bomb was selected at first, which leaves 2
    // options: either zero hasn't been chosen, which stops the search
    // immediately OR the number is zero, but a bomb can only be surrounded by
    // non null numbers and the search stops when finding them.
    if (g.getValue(p) != NOT) {
        return;
    }

    // Recursively search the surroundings if they haven't been searched yet
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            const pair<int, int> Q = make_pair(p.first + i, p.second + j);
            if (this->revealed.count(Q) == 0) {
                reveal(Q, g);
            }
        }
    }
}
