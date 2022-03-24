#include "input.hpp"
#include "mines.hpp"

int main() {
    constexpr int ROWS = 6;
    constexpr int COLS = 6;
    constexpr int NUM_BOMBS = 9;
    Mines g(ROWS, COLS, NUM_BOMBS);

    g.print();
    Input::greetAction();

    while (!g.isGameOver()) {
        g.getInput();
        g.update();
        if (!g.isGameOver()) {
            g.print();
        }
    }
}
