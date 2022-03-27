#include "color.hpp"
#include "grid.hpp"
#include "input.hpp"
#include <gtest/gtest.h>

using namespace std;

TEST(getPosition, format) {
    string testInput = "incorrect format\n";
    string expected = "Escolha uma posição: \nEntrada Inválida. Atente-se aos "
                      "exemplos de entrada.\n";

    stringstream fakeInput(testInput);
    ostringstream fakeOutput;

    Input::getPosition(fakeInput, fakeOutput);
    string actual = fakeOutput.str();

    EXPECT_EQ(actual, expected);
}

TEST(getPosition, eof) {
    string testInput;

    stringstream fakeInput(testInput);
    ostringstream fakeOutput;
    ostringstream fakeErr;

    ASSERT_DEATH(Input::getPosition(fakeInput, fakeOutput),
                 "\nA entrada de dados foi interrompida. Saindo.\n");
}

TEST(getAction, format) {
    string testInput = "incorrect format\n";
    string expected =
        "Escolha uma ação: \nAtenção! A ação é UMA letra minúscula.\n\n";

    stringstream fakeInput(testInput);
    ostringstream fakeOutput;

    Input::getAction(fakeInput, fakeOutput);
    string actual = fakeOutput.str();

    EXPECT_EQ(actual, expected);
}

TEST(getAction, eof) {
    string testInput;

    stringstream fakeInput(testInput);
    ostringstream fakeOutput;

    ASSERT_DEATH(Input::getAction(fakeInput, fakeOutput),
                 "\nA entrada de dados foi interrompida. Saindo.\n");
}

TEST(getAction, domain) {
    // "x" não é uma ação: (m)ark, (u)nmark, (s)how
    string testInput = "x\n";
    string expected = "Escolha uma ação: \nAtenção! A ação deve ser uma das "
                      "letras minúsculas apresentadas\n\n";

    stringstream fakeInput(testInput);
    ostringstream fakeOutput;

    Input::getAction(fakeInput, fakeOutput);
    string actual = fakeOutput.str();

    EXPECT_EQ(actual, expected);
}

TEST(grid, constructor) {
    ostringstream fakeOutput;

    EXPECT_DEATH(Grid g(0, 4, fakeOutput),
                 "Number of rows needs to be a positive integer");
    EXPECT_DEATH(Grid g(4, 0, fakeOutput),
                 "Number of columns needs to be a positive integer");
}

TEST(grid, printHeader) {
    ostringstream fakeOutput;
    string expected = "\n" BLU "   │ " RESET "1" BLU " │ " RESET "2\n";
    Grid g(4, 4, fakeOutput);

    g.printHeader();
    string actual = fakeOutput.str();

    EXPECT_EQ(expected, actual);
}

TEST(grid, printSeparator) {
    ostringstream fakeOutput;
    string expected = BLU "───┼" RESET BLU "───┼" RESET BLU "───\n" RESET;
    Grid g(4, 4, fakeOutput);

    g.printSeparator();
    string actual = fakeOutput.str();

    EXPECT_EQ(expected, actual);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
