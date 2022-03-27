#include "mines.hpp"
#include "actions.hpp"
#include "input.hpp"
#include "logic.hpp"
#include "msgassert.hpp"
#include <iostream>

using std::cerr;
using std::cin;
using std::cout;
using std::make_pair;

Mines::Mines(const int &_rows, const int &_cols, const int &_bombs)
    : grid(_rows + 2, _cols + 2, cout), logic(_bombs, cout) {
    assert(_bombs < _rows * _cols, "Too many bombs");

    this->logic.placeBombs(this->grid);
    this->grid.initialize();
}

void Mines::input() {
    do {
        this->action = Input::getAction(cin, cout);
    } while (this->action == 0);
    do {
        this->pos = Input::getPosition(cin, cout);
    } while (this->pos == make_pair(0, 0));
}

void Mines::update() {
    if (this->grid.isOutOfBounds(this->pos)) {
        cout << "\nOops. Essa posição não é válida.\n\n";
    } else {
        switch (this->action) {
        case Actions::SHOW:
            this->logic.handleReveal(this->pos, this->grid);
            break;
        case Actions::MARK:
            this->logic.handleMark(this->pos);
            break;
        case Actions::UNMARK:
            this->logic.handleUnmark(this->pos);
            break;
        default:
            cerr << "\nAção ilegal\n\n";
            exit(1);
        }
    }
    if (this->logic.hasExploded()) {
        cout << "\nVocê perdeu! Que pena!\n\n";
        this->gameOver = true;
    }
    if (this->logic.hasWon(this->grid.size())) {
        cout << "\nVocê venceu! Parabéns!\n\n";
        this->gameOver = true;
    }
}

void Mines::print() const {
    this->grid.print(this->logic.marked, this->logic.revealed);
}
