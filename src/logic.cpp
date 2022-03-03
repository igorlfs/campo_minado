#include "logic.hpp"
#include "actions.hpp"
#include "random.hpp"
#include <iostream>
#include <utility>

using std::make_pair;
using std::pair;

void Logic::placeBombs(Grid &g) {
    for (int i = 0; i < this->numBombs; ++i) {
        pair<int, int> p;
        do {
            p = {Random::rng(1, g.getRows() - 2),
                 Random::rng(1, g.getCols() - 2)};
        } while (this->bombs.find(p) != this->bombs.end());
        g.placeBomb(p);
        this->bombs.insert(p);
    }
}

bool Logic::hasWon(const Grid &g) const {
    const bool marks = this->marked == this->bombs;
    const bool reveals = this->revealed.size() == g.size() - this->bombs.size();
    return (marks && reveals);
}

void Logic::update(const Grid &g, const pair<int, int> &p) {
    switch (this->action) {
    case Actions::show: handleReveal(p, g); break;
    case Actions::mark: handleMark(p); break;
    case Actions::undo: handleUndo(p); break;
    default: std::cerr << "\nAção ilegal 😵"; exit(1);
    }
}

void Logic::handleReveal(const std::pair<int, int> &p, const Grid &g) {
    if (this->bombs.find(p) != this->bombs.end()) throw exploded();
    if (this->revealed.find(p) != this->revealed.end()) throw repeated();
    reveal(p, g);
}

void Logic::reveal(const pair<int, int> &p, const Grid &g) {
    // Boundary check
    if (g.isOutOfBounds(p)) return;

    // Reveal
    this->revealed.insert(p);

    // Remove marked position if necessary
    if (this->marked.find(p) != this->marked.end()) this->marked.erase(p);

    // Stop searching when a non null number is found;
    // Note that while searching, it's impossible to find a bomb:
    // we check separately if a bomb was selected at first, which leaves 2
    // options: either zero hasn't been chosen, which stops the search
    // immediately OR the number is zero, but a bomb can only be surrounded by
    // non null numbers and the search stops when finding them.
    if (g.getValue(p) != '0') return;

    // Recursively search the surroundings if they haven't been searched yet
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            const pair<int, int> q = make_pair(p.first + i, p.second + j);
            if (this->revealed.find(q) == this->revealed.end())
                this->reveal(q, g);
        }
    }
}

void Logic::handleUndo(const pair<int, int> &p) {
    if (this->marked.find(p) == this->marked.end()) throw notmarked();
    this->marked.erase(p);
}

void Logic::handleMark(const pair<int, int> &p) {
    if (this->revealed.find(p) != this->revealed.end()) throw unmarkable();
    if (this->marked.find(p) != this->marked.end()) throw repeated();
    this->marked.insert(p);
}
