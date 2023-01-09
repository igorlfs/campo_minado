#include "input.hpp"
#include "mines.hpp"

int main() {
    constexpr int ROWS = 6;
    constexpr int COLS = 6;
    constexpr int NUM_BOMBS = 9;
    Mines game(ROWS, COLS, NUM_BOMBS);

    game.print();

    Input::greetAction();
    Input::greetPosition();

    while (!game.isGameOver()) {
        game.input();
        game.update();
        game.print();
    }
}
