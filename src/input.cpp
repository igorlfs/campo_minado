#include "input.hpp"
#include "actions.hpp"
#include <iostream>
#include <regex>

using std::cerr;
using std::cin;
using std::cout;
using std::getline;
using std::make_pair;
using std::pair;
using std::regex;
using std::regex_match;
using std::string;
using std::stringstream;

void Input::greetPosition() {
    cout << "\nPosições válidas:\n"
            "Uma posição válida é composta por uma letra MAIÚSCULA"
         << " e um número (necessariamente nessa ordem).\n"
         << "Exemplos de posições válidas são: A2, C5, D4\n\n";
}

pair<int, int> Input::getPosition() {
insertAgain:
    cout << "Escolha uma posição: ";
    try {
        const regex EXPECTED_FORMAT("[A-Z][1-9][0-9]*");
        string readLine;
        char row;
        int column;

        getline(cin, readLine);
        if (cin.eof()) {
            throw interrupt();
        }
        if (!regex_match(readLine, EXPECTED_FORMAT)) {
            throw invalidPositionFormat();
        }

        stringstream ss(readLine);
        ss >> row >> column;
        return make_pair((int)(row - (int)'A') + 1, column);
    } catch (interrupt e) {
        cerr << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    } catch (invalidPositionFormat e) {
        cout << "\nEntrada Inválida. Atente-se aos exemplos de entrada.\n";
        goto insertAgain;
    }
}

void Input::greetAction() {
    cout << "Ações disponíveis: \n"
         << Actions::SHOW << " - revelar: você sabe 😉\n"
         << Actions::MARK
         << " - marcar: sinalize onde você suspeita que existe uma bomba. "
            "Necessário para ganhar.\n"
         << Actions::UNMARK
         << " - desmarcar: use se mudou de ideia em relação a uma "
            "posição marcada\n\n";
}

char Input::getAction() {
insertAgain:
    cout << "Escolha uma ação: ";
    try {
        const regex EXPECTED_FORMAT("[a-z]");
        string readLine;
        char action;

        getline(cin, readLine);

        if (cin.eof()) {
            throw interrupt();
        }
        if (!regex_match(readLine, EXPECTED_FORMAT)) {
            throw invalidActionFormat();
        }

        stringstream ss(readLine);
        ss >> action;

        if (action != Actions::SHOW && action != Actions::MARK &&
            action != Actions::UNMARK) {
            throw invalidAction();
        }

        return action;
    } catch (interrupt e) {
        cerr << "\n\nA entrada de dados foi interrompida. Saindo.\n\n";
        exit(1);
    } catch (invalidActionFormat e) {
        cout << "\nAtenção! A ação é UMA letra minúscula.\n\n";
        goto insertAgain;
    } catch (invalidAction e) {
        cout << "\nAtenção! A ação dever ser uma das letras minúsculas "
                "apresentadas\n\n";
        goto insertAgain;
    }
}
