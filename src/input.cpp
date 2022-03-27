#include "input.hpp"
#include "actions.hpp"
#include "msgassert.hpp"
#include <regex>

using std::getline;
using std::istream;
using std::make_pair;
using std::ostream;
using std::pair;
using std::regex;
using std::regex_match;
using std::string;
using std::stringstream;

void Input::greetPosition(ostream &outStream) {
    outStream << "\nPosições válidas:\n"
                 "Uma posição válida é composta por uma letra MAIÚSCULA"
              << " e um número (necessariamente nessa ordem).\n"
              << "Exemplos de posições válidas são: A2, C5, D4\n\n";
}

pair<int, int> Input::getPosition(istream &inStream, ostream &outStream) {
    outStream << "Escolha uma posição: ";
    const regex EXPECTED_FORMAT("[A-Z][1-9][0-9]*");
    string readLine;
    char row;
    int column;

    getline(inStream, readLine);
    assertUser(!inStream.eof(), "A entrada de dados foi interrompida. Saindo.");

    if (!regex_match(readLine, EXPECTED_FORMAT)) {
        outStream << "\nEntrada Inválida. Atente-se aos exemplos de entrada.\n";
        return {0, 0};
    }

    stringstream ss(readLine);
    ss >> row >> column;
    return make_pair((row - (int)'A') + 1, column);
}

void Input::greetAction(ostream &outStream) {
    outStream << "Ações disponíveis: \n"
              << Actions::SHOW << " - revelar: você sabe 😉\n"
              << Actions::MARK
              << " - marcar: sinalize onde você suspeita que existe uma bomba. "
                 "Necessário para ganhar.\n"
              << Actions::UNMARK
              << " - desmarcar: use se mudou de ideia em relação a uma "
                 "posição marcada\n\n";
}

char Input::getAction(istream &inStream, ostream &outStream) {
    outStream << "Escolha uma ação: ";
    const regex EXPECTED_FORMAT("[a-z]");
    string readLine;
    char action;

    getline(inStream, readLine);

    assertUser(!inStream.eof(), "A entrada de dados foi interrompida. Saindo.");
    if (!regex_match(readLine, EXPECTED_FORMAT)) {
        outStream << "\nAtenção! A ação é UMA letra minúscula.\n\n";
        return 0;
    }

    stringstream ss(readLine);
    ss >> action;

    if (action != Actions::SHOW && action != Actions::MARK &&
        action != Actions::UNMARK) {
        outStream << "\nAtenção! A ação deve ser uma das letras minúsculas "
                     "apresentadas\n\n";
        return 0;
    }

    return action;
}
