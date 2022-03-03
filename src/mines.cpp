#include "mines.hpp"
#include "input.hpp"
#include "logic.hpp"
#include "msgassert.hpp"
#include <iostream>

using std::cout;
using std::make_pair;

Mines::Mines(const int &_rows, const int &_cols, const int &_bombs)
    : grid(_rows + 2, _cols + 2), engine(_bombs) {
    assert(_bombs < _rows * _cols, "Too many bombs");

    this->engine.placeBombs(this->grid);
    this->grid.initialize();
}

void Mines::getInput() {
    this->engine.setAction(Input::getAction());

    // Only greet once
    if (this->position == make_pair(0, 0)) Input::greetPosition();
    this->position = Input::getPosition();
}

void Mines::update() {
    if (this->grid.isOutOfBounds(this->position)) {
        cout << "\nOops. Essa posição não é válida.\n\n";
    } else {
        try {
            this->engine.update(this->grid, this->position);
        } catch (exploded e) {
            cout << "\n\nVocê perdeu! Só te resta chorar agora 😢\n\n";
            this->gameOver = true;
        } catch (repeated e) {
            cout << "\nVocê já realizou essa ação nessa posição.\n\n";
        } catch (unmarkable e) {
            cout << "\nVocê não pode marcar uma posição revelada.\n\n";
        } catch (notmarked e) {
            cout << "\nVocê não pode desmarcar uma posição não marcada.\n\n";
        }
    }
    if (this->engine.hasWon(this->grid)) this->gameOver = true;
}

void Mines::print() const {
    this->grid.print(this->engine.marked, this->engine.revealed);
}
