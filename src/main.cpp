#include "input.hpp"
#include "mines.hpp"

int main() {
    constexpr int x = 6;
    constexpr int y = 6;
    constexpr int numBombs = 9;
    Mines g(x, y, numBombs);

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
