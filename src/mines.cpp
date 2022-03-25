#include "mines.hpp"
#include "actions.hpp"
#include "input.hpp"
#include "logic.hpp"
#include "msgassert.hpp"
#include <iostream>

using std::cout;
using std::make_pair;

Mines::Mines(const int &_rows, const int &_cols, const int &_bombs)
    : grid(_rows + 2, _cols + 2), logic(_bombs) {
    assert(_bombs < _rows * _cols, "Too many bombs");

    this->logic.placeBombs(this->grid);
    this->grid.initialize();
}

void Mines::input() {
    this->action = Input::getAction();
    this->pos = Input::getPosition();
}

void Mines::update() {
    if (this->grid.isOutOfBounds(this->pos)) {
        cout << "\nOops. Essa posição não é válida.\n\n";
    } else {
        try {
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
                std::cerr << "\nAção ilegal\n\n";
                exit(1);
            }
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
    if (this->logic.hasWon(this->grid.size())) {
        cout << "\nVocê venceu! Parabéns!\n\n";
        this->gameOver = true;
    }
}

void Mines::print() const {
    this->grid.print(this->logic.marked, this->logic.revealed);
}
