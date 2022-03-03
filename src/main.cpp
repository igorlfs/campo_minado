#include "input.hpp"
#include "mines.hpp"

int main() {
    Mines g(6, 6, 6);

    g.print();
    Input::greetAction();

    while (!g.isGameOver()) {
        g.getInput();
        g.update();
        if (!g.isGameOver()) g.print();
    }
}
